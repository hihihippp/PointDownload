#ifndef DLDATACONVERTER_H
#define DLDATACONVERTER_H

#include <QObject>
#include <QTimer>
#include <QQmlEngine>
#include "Download/unifiedinterface.h"
#include "urlserver.h"

class DLDataConverter : public QObject
{
    Q_OBJECT
public:
    static DLDataConverter * getInstance();
    static QObject * dataObj(QQmlEngine *engine, QJSEngine *scriptEngine);
    //qml中能直接调用此方法
    Q_INVOKABLE void controlItem(const QString &dtype, const QString &otype, QString URL);//dtype:DownloadType otype:OperationType
    Q_INVOKABLE void suspendAllDownloading();
    Q_INVOKABLE void resumeAllDownloading();

signals:
    void taskAdded(const QString& infoString);
    void downloadedAdded(const QString& infoString);
    void trashAdded(const QString& infoString);
    void taskCompleted(const QString& infoString);
    void taskRemoved(const QString& infoString);
    //dlType：Downloading、Downloaded、DownloadTrash
    void sFileNameChange(QString dlType, QString dlURL,  QString fileName);
    void sFileInfoChange(QString dlType, const TaskInfo &taskInfo);
    //dlState,文件状态 , "dlstate_downloading" 或者是 "dlstate_suspend",经常更新
    void sDLStateChange(QString dlURL, QString dlState);
    void sDLSpeedChange(QString dlURL, QString dlSpeed);
    void sDLProgressChange(QString dlURL, double progress);
    void sThunderOfflineSpeedChange(QString dlURL, QString offlineSpeed);
    void sThunderHightSpeedChange(QString dlURL, QString hightSpeed);

    //控制反馈
    void sControlFeedback(QString dlType, QString dlURL, QString operationType, bool result);


    //通知界面更新下载项列表的排列
    void sRefreshDownloadingItem();
public slots:
    //用于接收统一接口类信号的接收
    //为列表面板添加项
    void addDownloadingItem(const TaskInfo &taskInfo);
    void addDownloadedItem(const TaskInfo &taskInfo);
    void addDownloadTrashItem(const TaskInfo &taskInfo);

    void slotGetDownloadingInfo(DownloadingItemInfo infoList);
    //操作返回值
    void slotGetContrlFeedback(DownloadType dtype,OperationType otype, QString URL,bool result);

    void initURLServer();

private:
    explicit DLDataConverter(QObject *parent = 0);

    void initConnection();
private:
    static DLDataConverter * dlDataConverter;
};
#endif // DLDATACONVERTER_H
