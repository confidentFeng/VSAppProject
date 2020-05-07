#include "HttpClient.h"

#include <QDebug>
#include <QFile>
#include <QHash>
#include <QUrlQuery>
#include <QHttpPart>
#include <QHttpMultiPart>

/*-----------------------------------------------------------------------------|
|                              HttpClientPrivate                              |
|----------------------------------------------------------------------------*/
/**
* @brief ���������
*
* ע: UPLOAD ���� HTTP Method��ֻ��Ϊ���ϴ�ʱ������������⴦��������
*/
enum class HttpClientRequestMethod {
	GET, POST, PUT, DELETE, UPLOAD
};

/**
* @brief ���� HttpClientPrivate �����ݳ�Ա���������첽 lambda ��ʹ�� = ��ֵ�ķ�ʽ���ʡ�
*/
class HttpClientPrivateCache {
public:
	std::function<void(const QString &)>      successHandler = nullptr;
	std::function<void(const QString &, int)>    failHandler = nullptr;
	std::function<void()>                    completeHandler = nullptr;
	bool debug = false;
	bool internal = false;
	QString charset;
	QNetworkAccessManager* manager = nullptr;
};

/**
* @brief HttpClient �ĸ����࣬��װ��ϣ����¶���ͻ��˵����ݺͷ�����ʹ�� HttpClient ֻ��¶��Ҫ�� API ���ͻ��ˡ�
*/
class HttpClientPrivate {
	friend class HttpClient;

	HttpClientPrivate(const QString &url);
	~HttpClientPrivate();

	/**
	* @brief ���� HttpClientPrivate �����ݳ�Ա
	*
	* @return ���� HttpClientPrivateCache �������
	*/
	HttpClientPrivateCache cache();

	/**
	* @brief ��ȡ Manager����������� manager �򷵻ش� manager�������´���һ�� manager��Ĭ�ϻ��Զ�����һ�� manager��
	*        ʹ�ô���� manager �� interval ������Ϊ false���Զ������� manager ������ interval Ϊ true
	*
	* @return ���� QNetworkAccessManager ����
	*/
	QNetworkAccessManager* getManager();

	/**
	* @brief ʹ���û��趨�� URL������ͷ�������ȴ��� Request
	*
	* @param d      HttpClientPrivate �Ķ���
	* @param method ���������
	* @return ���ؿ�����ִ������� QNetworkRequest
	*/
	static QNetworkRequest createRequest(HttpClientPrivate *d, HttpClientRequestMethod method);

	/**
	* @brief ִ������ĸ�������
	*
	* @param d      HttpClientPrivate �Ķ���
	* @param method ���������
	*/
	static void executeQuery(HttpClientPrivate *d, HttpClientRequestMethod method);

	/**
	* @brief �ϴ��ļ���������
	*
	* @param d     HttpClientPrivate �Ķ���
	* @param paths Ҫ�ϴ����ļ���·��(path �� data ����ͬʱʹ��)
	* @param data  Ҫ�ϴ����ļ�������
	*/
	static void upload(HttpClientPrivate *d, const QStringList &paths, const QByteArray &data);

	/**
	* @brief ʹ�� GET �������أ����ص��ļ����浽 savePath
	*
	* @param d        HttpClientPrivate �Ķ���
	* @param savePath ���ص��ļ�����·��
	*/
	static void download(HttpClientPrivate *d, const QString &savePath);

	/**
	* @brief ʹ�� GET �������أ��������ݿɶ�ȡʱ�ص� readyRead(), ����������Ӧ���� readyRead() ������ݱ��浽�ļ�
	*
	* @param readyRead �����ݿɶ�ȡʱ�Ļص� lambda ����
	*/
	static void download(HttpClientPrivate *d, std::function<void(const QByteArray &)> readyRead);

	/**
	* @brief ��ȡ��������Ӧ������
	*
	* @param reply   ����� QNetworkReply ����
	* @param charset ������Ӧ���ַ�����Ĭ��ʹ�� UTF-8
	* @return ���ط���������Ӧ���ַ���
	*/
	static QString readReply(QNetworkReply *reply, const QString &charset = "UTF-8");

	/**
	* @brief ��������Ĵ�����
	*
	* @param cache          HttpClientPrivateCache �������
	* @param reply          QNetworkReply ���󣬲���Ϊ NULL
	* @param successMessage ����ɹ�����Ϣ
	* @param failMessage    ����ʧ�ܵ���Ϣ
	*/
	static void handleFinish(HttpClientPrivateCache cache, QNetworkReply *reply, const QString &successMessage, const QString &failMessage);

	/////////////////////////////////////////////////// ��Ա���� //////////////////////////////////////////////
	QString   url;                            // ����� URL
	QString   json;                           // ����Ĳ���ʹ�� Json ��ʽ
	QUrlQuery params;                         // ����Ĳ���ʹ�� Form ��ʽ
	QString   charset = "UTF-8";              // ������Ӧ���ַ���
	QHash<QString, QString> headers;          // ����ͷ
	QNetworkAccessManager *manager = nullptr; // ִ�� HTTP ����� QNetworkAccessManager ����
	bool useJson = false;                    // Ϊ true ʱ����ʹ�� Json ��ʽ���ݲ���������ʹ�� Form ��ʽ���ݲ���
	bool debug = false;                    // Ϊ true ʱ�������� URL �Ͳ���
	bool internal = true;                     // �Ƿ�ʹ���Զ������� manager

	std::function<void(const QString &)>   successHandler = nullptr; // �ɹ��Ļص�����������Ϊ��Ӧ���ַ���
	std::function<void(const QString &, int)> failHandler = nullptr; // ʧ�ܵĻص�����������Ϊʧ��ԭ��� HTTP status code
	std::function<void()>                 completeHandler = nullptr; // �����Ļص��������޲���
};

HttpClientPrivate::HttpClientPrivate(const QString &url) : url(url) { }

HttpClientPrivate::~HttpClientPrivate() {
	manager = nullptr;
	successHandler = nullptr;
	failHandler = nullptr;
	completeHandler = nullptr;
}

// ���� HttpClientPrivate �����ݳ�Ա
HttpClientPrivateCache HttpClientPrivate::cache() {
	HttpClientPrivateCache cache;

	cache.successHandler = successHandler;
	cache.failHandler = failHandler;
	cache.completeHandler = completeHandler;
	cache.debug = debug;
	cache.internal = internal;
	cache.charset = charset;
	cache.manager = getManager();

	return cache;
}

// ִ������ĸ�������
void HttpClientPrivate::executeQuery(HttpClientPrivate *d, HttpClientRequestMethod method) {
	// 1. ������Ҫ�ı������� lambda ��ʹ�� = �������ֵ���� (����ʹ������ &����Ϊ d �Ѿ�������)
	// 2. ����������Ҫ�ı���
	// 3. ���� method ִ�в�ͬ������
	// 4. �������ʱ��ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����

	// [1] ������Ҫ�ı������� lambda ��ʹ�� = �������ֵ���� (����ʹ������ &����Ϊ d �Ѿ�������)
	HttpClientPrivateCache cache = d->cache();

	// [2] ����������Ҫ�ı���
	QNetworkRequest request = HttpClientPrivate::createRequest(d, method);
	QNetworkReply    *reply = nullptr;

	// [3] ���� method ִ�в�ͬ������
	switch (method) {
	case HttpClientRequestMethod::GET:
		reply = cache.manager->get(request);
		break;
	case HttpClientRequestMethod::POST:
		reply = cache.manager->post(request, d->useJson ? d->json.toUtf8() : d->params.toString(QUrl::FullyEncoded).toUtf8());
		break;
	case HttpClientRequestMethod::PUT:
		reply = cache.manager->put(request, d->useJson ? d->json.toUtf8() : d->params.toString(QUrl::FullyEncoded).toUtf8());
		break;
	case HttpClientRequestMethod::DELETE:
		reply = cache.manager->deleteResource(request);
		break;
	default:
		break;
	}

	// [4] �������ʱ��ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����
	// �������ʱһ���Զ�ȡ������Ӧ����
	QObject::connect(reply, &QNetworkReply::finished, [=] {
		QString successMessage = HttpClientPrivate::readReply(reply, cache.charset.toUtf8());
		QString failMessage = reply->errorString();
		HttpClientPrivate::handleFinish(cache, reply, successMessage, failMessage);
	});
}

// ʹ�� GET �������أ����ص��ļ����浽 savePath
void HttpClientPrivate::download(HttpClientPrivate *d, const QString &savePath) {
	// 1. �������ļ���������ļ���������������
	// 2. ����������Ļص�����ע��ر��ͷ��ļ�����Ϊ
	// 3. �������ص����غ�����ʼ����
	QFile *file = new QFile(savePath);

	// [1] �������ļ���������ļ���������������
	if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		file->close();
		file->deleteLater();

		if (d->debug) {
			qDebug().noquote() << QString("[����] ���ļ�����: %1").arg(savePath);
		}

		if (nullptr != d->failHandler) {
			d->failHandler(QString("[����] ���ļ�����: %1").arg(savePath), -1);
		}

		return;
	}

	// [2] ����������Ļص�����ע��ر��ͷ��ļ�����Ϊ
	std::function<void()> userCompleteHandler = d->completeHandler;
	std::function<void()> injectedCompleteHandler = [=]() {
		// ����������ͷ��ļ�����
		file->flush();
		file->close();
		file->deleteLater();

		// ִ���û�ָ���Ľ����ص�����
		if (nullptr != userCompleteHandler) {
			userCompleteHandler();
		}
	};
	d->completeHandler = injectedCompleteHandler;

	// [3] �������ص����غ�����ʼ����
	HttpClientPrivate::download(d, [=](const QByteArray &data) {
		file->write(data);
	});
}

// ʹ�� GET �������أ��������ݿɶ�ȡʱ�ص� readyRead(), ����������Ӧ���� readyRead() ������ݱ��浽�ļ�
void HttpClientPrivate::download(HttpClientPrivate *d, std::function<void(const QByteArray &)> readyRead) {
	// 1. ������Ҫ�ı������� lambda ��ʹ�� = �������ֵ���� (����ʹ������ &����Ϊ d �Ѿ�������)
	// 2. ����������Ҫ�ı�����ִ������
	// 3. �����ݿɶ�ȡʱ�ص� readyRead()
	// 4. �������ʱ��ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����

	// [1] ������Ҫ�ı������� lambda ��ʹ�� = ��׽ʹ�� (����ʹ������ &����Ϊ d �Ѿ�������)
	HttpClientPrivateCache cache = d->cache();

	// [2] ����������Ҫ�ı�����ִ������
	QNetworkRequest request = HttpClientPrivate::createRequest(d, HttpClientRequestMethod::GET);
	QNetworkReply    *reply = cache.manager->get(request);

	// [3] �����ݿɶ�ȡʱ�ص� readyRead()
	QObject::connect(reply, &QNetworkReply::readyRead, [=] {
		readyRead(reply->readAll());
	});

	// [4] �������ʱ��ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����
	QObject::connect(reply, &QNetworkReply::finished, [=] {
		QString successMessage = "�������"; // �������ʱһ���Զ�ȡ������Ӧ����
		QString failMessage = reply->errorString();
		HttpClientPrivate::handleFinish(cache, reply, successMessage, failMessage);
	});
}

// �ϴ��ļ��������ݵ�ʵ��
void HttpClientPrivate::upload(HttpClientPrivate *d, const QStringList &paths, const QByteArray &data) {
	// 1. ������Ҫ�ı������� lambda ��ʹ�� = �������ֵ���� (����ʹ������ &����Ϊ d �Ѿ�������)
	// 2. ���� Form ���Ĳ��� Text Part
	// 3. �����ϴ��� File Part
	//    3.1 ʹ���ļ����� File Part
	//    3.2 ʹ�����ݴ��� File Part
	// 4. ����������Ҫ�ı�����ִ������
	// 5. �������ʱ�ͷ� multiPart �ʹ򿪵��ļ�����ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����

	// [1] ������Ҫ�ı������� lambda ��ʹ�� = ��׽ʹ�� (����ʹ������ &����Ϊ d �Ѿ�������)
	HttpClientPrivateCache cache = d->cache();

	// [2] ���� Form ���Ĳ��� Text Part
	QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
	QList<QPair<QString, QString> > paramItems = d->params.queryItems();
	for (int i = 0; i < paramItems.size(); ++i) {
		QString name = paramItems.at(i).first;
		QString value = paramItems.at(i).second;

		QHttpPart textPart;
		textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QString("form-data; name=\"%1\"").arg(name));
		textPart.setBody(value.toUtf8());
		multiPart->append(textPart);
	}

	if (paths.size() > 0) {
		// [3.1] ʹ���ļ����� File Part
		QString inputName = paths.size() == 1 ? "file" : "files"; // һ���ļ�ʱΪ file������ļ�ʱΪ files

		for (const QString &path : paths) {
			// path Ϊ��ʱ�����ϴ��ļ�
			if (path.isEmpty()) {
				continue;
			}

			// We cannot delete the file now, so delete it with the multiPart
			QFile *file = new QFile(path, multiPart);

			// ����ļ���ʧ�ܣ����ͷ���Դ���أ���ֹ�ϴ�
			if (!file->open(QIODevice::ReadOnly)) {
				QString failMessage = QString("���ļ�ʧ��[%2]: %1").arg(path).arg(file->errorString());

				if (cache.debug) {
					qDebug().noquote() << failMessage;
				}

				if (nullptr != cache.failHandler) {
					cache.failHandler(failMessage, -1);
				}

				multiPart->deleteLater();
				return;
			}

			// �����ļ�ʱ��name Ϊ�������˻�ȡ�ļ��Ĳ�������Ϊ file
			// ����ļ�ʱ��name Ϊ�������˻�ȡ�ļ��Ĳ�������Ϊ files
			// ע��: �������� Java ������ form-data
			// ע��: �������� PHP  ������ multipart/form-data
			QString disposition = QString("form-data; name=\"%1\"; filename=\"%2\"").arg(inputName).arg(file->fileName());
			QHttpPart filePart;
			filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(disposition));
			filePart.setBodyDevice(file);
			multiPart->append(filePart);
		}
	}
	else {
		// [3.2] ʹ�����ݴ��� File Part
		QString   disposition = QString("form-data; name=\"file\"; filename=\"no-name\"");
		QHttpPart dataPart;
		dataPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(disposition));
		dataPart.setBody(data);
		multiPart->append(dataPart);
	}

	// [4] ����������Ҫ�ı�����ִ������
	QNetworkRequest request = HttpClientPrivate::createRequest(d, HttpClientRequestMethod::UPLOAD);
	QNetworkReply    *reply = cache.manager->post(request, multiPart);

	// [5] �������ʱ�ͷ� multiPart ���ļ�����ȡ��Ӧ���ݣ��� handleFinish ��ִ�лص�����
	QObject::connect(reply, &QNetworkReply::finished, [=] {
		multiPart->deleteLater(); // �ͷ���Դ: multiPart + file

		QString successMessage = HttpClientPrivate::readReply(reply, cache.charset); // �������ʱһ���Զ�ȡ������Ӧ����
		QString failMessage = reply->errorString();
		HttpClientPrivate::handleFinish(cache, reply, successMessage, failMessage);
	});
}

// ��ȡ Manager����������� manager �򷵻ش� manager�������´���һ�� manager��Ĭ�ϻ��Զ�����һ�� manager
QNetworkAccessManager* HttpClientPrivate::getManager() {
	return internal ? new QNetworkAccessManager() : manager;
}

// ʹ���û��趨�� URL������ͷ�������ȴ��� Request
QNetworkRequest HttpClientPrivate::createRequest(HttpClientPrivate *d, HttpClientRequestMethod method) {
	// 1. ����� GET ���󣬲��Ҳ�����Ϊ�գ����������Ĳ������ŵ� URL ����
	// 2. ����ʱ�����ַ�Ͳ���
	// 3. ���� Content-Type
	// 4. �������ͷ�� request ��

	bool get = method == HttpClientRequestMethod::GET;
	bool upload = method == HttpClientRequestMethod::UPLOAD;
	bool withForm = !get && !upload && !d->useJson; // PUT��POST ���� DELETE ������ useJson Ϊ false
	bool withJson = !get && !upload &&  d->useJson; // PUT��POST ���� DELETE ������ useJson Ϊ true

													// [1] ����� GET ���󣬲��Ҳ�����Ϊ�գ����������Ĳ������ŵ� URL ����
	if (get && !d->params.isEmpty()) {
		d->url += "?" + d->params.toString(QUrl::FullyEncoded);
	}

	// [2] ����ʱ�����ַ�Ͳ���
	if (d->debug) {
		qDebug().noquote() << "[��ַ]" << d->url;

		if (withJson) {
			qDebug().noquote() << "[����]" << d->json;
		}
		else if (withForm || upload) {
			QList<QPair<QString, QString> > paramItems = d->params.queryItems();
			QString buffer; // �����ε��� qDebug() ���������Ϣ��ÿ�� qDebug() ���п�������кŵ�

							// ����ֵ�Եķ�ʽ�������
			for (int i = 0; i < paramItems.size(); ++i) {
				QString name = paramItems.at(i).first;
				QString value = paramItems.at(i).second;

				if (0 == i) {
					buffer += QString("[����] %1=%2\n").arg(name).arg(value);
				}
				else {
					buffer += QString("       %1=%2\n").arg(name).arg(value);
				}
			}

			if (!buffer.isEmpty()) {
				qDebug().noquote() << buffer;
			}
		}
	}

	// [3] ���� Content-Type
	// ����� POST ����useJson Ϊ true ʱ��� Json ������ͷ��useJson Ϊ false ʱ��� Form ������ͷ
	if (withForm) {
		d->headers["Content-Type"] = "application/x-www-form-urlencoded";
	}
	else if (withJson) {
		d->headers["Content-Type"] = "application/json; charset=utf-8";
	}

	// [4] �������ͷ�� request ��
	QNetworkRequest request(QUrl(d->url));
	for (auto i = d->headers.cbegin(); i != d->headers.cend(); ++i) {
		request.setRawHeader(i.key().toUtf8(), i.value().toUtf8());
	}

	return request;
}

// ��ȡ��������Ӧ������
QString HttpClientPrivate::readReply(QNetworkReply *reply, const QString &charset) {
	QTextStream in(reply);
	QString result;
	in.setCodec(charset.toUtf8());

	while (!in.atEnd()) {
		result += in.readLine();
	}

	return result;
}

// ��������Ĵ�����
void HttpClientPrivate::handleFinish(HttpClientPrivateCache cache, QNetworkReply *reply, const QString &successMessage, const QString &failMessage) {
	// 1. ִ������ɹ��Ļص�����
	// 2. ִ������ʧ�ܵĻص�����
	// 3. ִ����������Ļص�����
	// 4. �ͷ� reply �� manager ����

	if (reply->error() == QNetworkReply::NoError) {
		if (cache.debug) {
			qDebug().noquote() << QString("[����] �ɹ�: %1").arg(successMessage);
		}

		// [1] ִ������ɹ��Ļص�����
		if (nullptr != cache.successHandler) {
			cache.successHandler(successMessage);
		}
	}
	else {
		if (cache.debug) {
			qDebug().noquote() << QString("[����] ʧ��: %1").arg(failMessage);
		}

		// [2] ִ������ʧ�ܵĻص�����
		if (nullptr != cache.failHandler) {
			cache.failHandler(failMessage, reply->error());
		}
	}

	// [3] ִ����������Ļص�����
	if (nullptr != cache.completeHandler) {
		cache.completeHandler();
	}

	// [4] �ͷ� reply �� manager ����
	if (nullptr != reply) {
		reply->deleteLater();
	}

	if (cache.internal && nullptr != cache.manager) {
		cache.manager->deleteLater();
	}
}

/*-----------------------------------------------------------------------------|
|                                 HttpClient                                  |
|----------------------------------------------------------------------------*/

// ע��: ���첽������ HttpClient �� HttpClientPrivate ��Ա���� d �Ѿ���������������Ҫ�Ȼ�����ر���Ϊջ����ʹ�� = ��ֵ�ķ�ʽ����
HttpClient::HttpClient(const QString &url) : d(new HttpClientPrivate(url)) { }

HttpClient::~HttpClient() {
	delete d;
}

// ���� QNetworkAccessManager �����������
HttpClient& HttpClient::manager(QNetworkAccessManager *manager) {
	d->manager = manager;
	d->internal = (nullptr == manager);

	return *this;
}

// ���� debug Ϊ true ��ʹ�� debug ģʽ������ִ��ʱ�������� URL �Ͳ�����
HttpClient& HttpClient::debug(bool debug) {
	d->debug = debug;

	return *this;
}

// ���һ������Ĳ��������Զ�ε�����Ӷ������
HttpClient& HttpClient::param(const QString &name, const QVariant &value) {
	d->params.addQueryItem(name, value.toString());

	return *this;
}

// ��Ӷ������Ĳ���
HttpClient& HttpClient::params(const QMap<QString, QVariant> &ps) {
	for (auto iter = ps.cbegin(); iter != ps.cend(); ++iter) {
		d->params.addQueryItem(iter.key(), iter.value().toString());
	}

	return *this;
}

// �������Ĳ��� (������)��ʹ�� Json ��ʽ������ "{\"name\": \"Alice\"}"
HttpClient& HttpClient::json(const QString &json) {
	d->json = json;
	d->useJson = true;

	return *this;
}

// �������ͷ
HttpClient& HttpClient::header(const QString &name, const QString &value) {
	d->headers[name] = value;

	return *this;
}

// ��Ӷ������ͷ
HttpClient& HttpClient::headers(const QMap<QString, QString> nameValues) {
	for (auto i = nameValues.cbegin(); i != nameValues.cend(); ++i) {
		d->headers[i.key()] = i.value();
	}

	return *this;
}

// ע������ɹ��Ļص�����
HttpClient& HttpClient::success(std::function<void(const QString &)> successHandler) {
	d->successHandler = successHandler;

	return *this;
}

// ע������ʧ�ܵĻص�����
HttpClient& HttpClient::fail(std::function<void(const QString &, int)> failHandler) {
	d->failHandler = failHandler;

	return *this;
}

// ע����������Ļص����������ܳɹ�����ʧ�ܶ���ִ��
HttpClient& HttpClient::complete(std::function<void()> completeHandler) {
	d->completeHandler = completeHandler;

	return *this;
}

// ����������Ӧ�ı���
HttpClient& HttpClient::charset(const QString &cs) {
	d->charset = cs;

	return *this;
}

// ִ�� GET ����
void HttpClient::get() {
	HttpClientPrivate::executeQuery(d, HttpClientRequestMethod::GET);
}

// ִ�� POST ����
void HttpClient::post() {
	HttpClientPrivate::executeQuery(d, HttpClientRequestMethod::POST);
}

// ִ�� PUT ����
void HttpClient::put() {
	HttpClientPrivate::executeQuery(d, HttpClientRequestMethod::PUT);
}

// ִ�� DELETE ����
void HttpClient::remove() {
	HttpClientPrivate::executeQuery(d, HttpClientRequestMethod::DELETE);
}

// ʹ�� GET �������أ����ص��ļ����浽 savePath
void HttpClient::download(const QString &savePath) {
	HttpClientPrivate::download(d, savePath);
}

// �ϴ��ļ�
void HttpClient::upload(const QString &path) {
	QStringList paths = { path };
	HttpClientPrivate::upload(d, paths, QByteArray());
}

// �ϴ��ļ����ļ��������Լ���ȡ�� data ��
void HttpClient::upload(const QByteArray &data) {
	HttpClientPrivate::upload(d, QStringList(), data);
}

// �ϴ�����ļ�
void HttpClient::upload(const QStringList &paths) {
	HttpClientPrivate::upload(d, paths, QByteArray());
}