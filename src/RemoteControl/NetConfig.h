#pragma once
#include <windows.h>
#include <QPainter>
#include <QNetworkInterface>
#include <IPHlpApi.h>
#include <IPTypes.h>
#include <QRegExpValidator>
#include "common.h"
#include "MyPromptBox.h"
#include "XmlHelper.h"

#pragma comment (lib,"IPHlpApi.Lib")

class NetConfig : public QDialog
{
	Q_OBJECT

public:
	NetConfig(QDialog *parent = Q_NULLPTR, const bool& bIsWifi = true);
	~NetConfig();
	void SetBtnReturnText(const QString& strText); // 设置返回按钮的文本

signals:
	void BtnNextClicked(); // 下一步按钮的点击信号
	void BtnReturnClicked();
	void StackedWidgetClose(); // StackedWidget界面关闭的信号
	void NetConfigSuc(); // 网络配置成功的信号

private slots:
	void NextSlot(); // 下一步槽函数

private:
	void showEvent(QShowEvent * event); // 显示事件
	bool isDhcpEnabled(QString mac); // 检查DHCP服务是否开启

	QWidget *m_pWidgetChild; // 子界面
	QLabel *m_pLabTitle; // 标题标签
	QPushButton *m_pBtnClose; // 关闭按钮
	QRadioButton *m_pRadioAuto; // 自动获取IP单选框
	QLabel *m_pLabAuto; // 自动获取IP标签
	QRadioButton *m_pRadioManual; // 手动获取IP单选框
	QLabel *m_pLabManual; // 手动获取IP标签
	QLabel *m_pLabIP; // IP标签
	QLineEdit *m_pEditIP; // IP文本框
	QLabel *m_pLabMask; // 子网掩码标签
	QLineEdit *m_pEditMask; // 子网掩码文本框
	QLabel *m_pLabGway; // 默认网关标签
	QLineEdit *m_pEditGway; // 默认网关文本框
	QPushButton *m_pBtnReturn; // 返回按钮
	QPushButton *m_pBtnNext; // 下一步按钮

	QString humanReadableName; // 网卡名称
	bool m_isManualFlag; // 是否为手动获取的标志位
	bool m_bIsWifi; // 是否为wifi的标志位
};
