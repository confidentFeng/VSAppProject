#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <functional>
#include <QMap>
#include <QVariant>
#include <QStringList>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class HttpClientPrivate;

/**
* �� QNetworkAccessManager �򵥷�װ�� HTTP ���ʿͻ��ˣ��� GET��POST��PUT��DELETE���ϴ������صȲ�����
* ��ִ������ǰ������Ҫ�Ĳ����ͻص�����:
*     1. ���� header() ��������ͷ
*     2. ���� param() ���ò�����ʹ�� Form ���ķ�ʽ�ύ����GET ����� query parameters Ҳ������������
*     3. ���� json() ���� JSON �ַ����� request body��Content-Type Ϊ application/json��
*        ��ȻҲ���Բ��� JSON ��ʽ����ʹ�� request body �����������ʹ�� JSON ��ʽ���ݸ��Ӷ��󣬹�����Ϊ json
*     4. ���� success() ע������ɹ��Ļص�����
*     5. ���� fail() ע������ʧ�ܵĻص�����
*     6. ���� complete() ע����������Ļص�����
*        success(), fail(), complete() �Ļص������ǿ�ѡ�ģ�������Ҫע���Ӧ�Ļص�������Ҳ����һ������ע��
* Ȼ�������������͵��� get(), post(), put(), remove(), download(), upload() ִ�� HTTP ����
*
* Ĭ�� HttpClient �ᴴ��һ�� QNetworkAccessManager���������ʹ��Ĭ�ϵģ����� manager() ���뼴�ɡ�
* ���� debug(true) ����Ϊ����ģʽ�����������Ϣ�� URL�������ȡ�
*/
class HttpClient {
public:
	HttpClient(const QString &url);
	~HttpClient();

	/**
	* @brief ÿ����һ�� QNetworkAccessManager ���󶼻ᴴ��һ���̣߳���Ƶ���ķ�������ʱ��Ϊ�˽�ʡ�߳���Դ��
	*     ���Դ��� QNetworkAccessManager ����������� (�����ᱻ HttpClient ɾ�����û���Ҫ�Լ��ֶ�ɾ��)��
	*     ���û��ʹ�� manager() ����һ�� QNetworkAccessManager���� HttpClient ���Զ��Ĵ���һ�������������������ɺ��Զ�ɾ������
	*
	* @param  manager ִ�� HTTP ����� QNetworkAccessManager ����
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& manager(QNetworkAccessManager *manager);

	/**
	* @brief  ���� debug Ϊ true ��ʹ�� debug ģʽ������ִ��ʱ�������� URL �Ͳ�����
	*
	* @param  debug �Ƿ����õ���ģʽ
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& debug(bool debug);

	/**
	* @brief ���һ������Ĳ��������Զ�ε�����Ӷ������
	*
	* @param name  ����������
	* @param value ������ֵ
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& param(const QString &name, const QVariant &value);

	/**
	* @brief ��Ӷ������Ĳ���
	*
	* @param ps QMap ���͵Ĳ�����key Ϊ��������value Ϊ����ֵ
	*           ����ʹ�� {{"name", 1}, {"box", 2}} �ķ�ʽ���� QMap ����
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& params(const QMap<QString, QVariant> &ps);

	/**
	* @brief �������Ĳ��� (������)��ʹ�� Json ��ʽ������ "{\"name\": \"Alice\"}"
	*
	* @param json ������ (request body) Ϊ Json ��ʽ�Ĳ����ַ���
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& json(const QString &json);

	/**
	* @brief �������ͷ
	*
	* @param name  ����ͷ������
	* @param value ����ͷ��ֵ
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& header(const QString &name, const QString &value);

	/**
	* @brief ��Ӷ������ͷ
	*
	* @param nameValues ����ͷ�����ֺ�ֵ��
	*                   ����ʹ�� {{"name", 1}, {"box", 2}} �ķ�ʽ���� QMap ����
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& headers(const QMap<QString, QString> nameValues);

	/**
	* @brief ע������ɹ��Ļص�����
	*
	* @param successHandler �ɹ��Ļص�����������Ϊ��Ӧ���ַ���
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& success(std::function<void(const QString &)> successHandler);

	/**
	* @brief ע������ʧ�ܵĻص�����
	*
	* @param failHandler ʧ�ܵĻص�����������Ϊʧ��ԭ��� HTTP ״̬��
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& fail(std::function<void(const QString &, int)> failHandler);

	/**
	* @brief ע����������Ļص����������ܳɹ�����ʧ����������󶼻�ִ��
	*
	* @param completeHandler ��ɵĻص��������޲���
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& complete(std::function<void()> completeHandler);

	/**
	* @brief ����������Ӧ���ַ�����Ĭ��ʹ�� UTF-8
	*
	* @param cs �ַ���
	* @return ���� HttpClient �����ã�����������ʽ����
	*/
	HttpClient& charset(const QString &cs);

	/**
	* @brief ִ�� GET ����
	*/
	void get();

	/**
	* @brief ִ�� POST ����
	*/
	void post();

	/**
	* @brief ִ�� PUT ����
	*/
	void put();

	/**
	* @brief ִ�� DELETE �������� delete �� C++ ���������������ͬ��� remove
	*        ע��: Qt �ṩ�� DELETE �����ǲ�֧�ִ��ݲ����ģ�
	*        ��ο� QNetworkAccessManager::deleteResource(const QNetworkRequest &request)
	*/
	void remove();

	/**
	* @brief ʹ�� GET �������أ����ص��ļ����浽 savePath
	*
	* @param savePath ���ص��ļ�����·��
	*/
	void download(const QString &savePath);

	/**
	* @brief �ϴ������ļ�
	*        ʹ�� POST �ϴ����������˻�ȡ�ļ��Ĳ�����Ϊ file
	*
	* @param path Ҫ�ϴ����ļ���·��
	*/
	void upload(const QString &path);

	/**
	* @brief �ϴ��ļ����ļ��������Ѿ���ȡ�� data ��
	*        ʹ�� POST �ϴ����������˻�ȡ�ļ��Ĳ�����Ϊ file
	*
	* @param path Ҫ�ϴ����ļ���·��
	*/
	void upload(const QByteArray &data);

	/**
	* @brief �ϴ�����ļ�
	*        ʹ�� POST �ϴ����������˻�ȡ�ļ��Ĳ�����Ϊ files
	*
	* @param paths Ҫ�ϴ����ļ���·��
	*/
	void upload(const QStringList &paths);

private:
	HttpClientPrivate *d;
};

#endif // HTTPCLIENT_H