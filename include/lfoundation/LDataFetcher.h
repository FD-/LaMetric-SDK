#pragma once

#include <QtCore/QObject>

#include "LFetchTask.h"

class LDataFetcherPrivate;

class LDataFetcher : public QObject {
    Q_OBJECT

public:
	enum UpdateReason {
		UpdateReasonInternetAvailabilityChanged = 1
	};

	LDataFetcher(QObject *parent);

	void addFetchTask(LFetchTask *task, int intervalSeconds, bool runImmediately);
	/* Deprecated */
	void addFetchTask(int id, LFetchTask *task, int intervalSeconds, bool runImmediately);
	bool containsFetchTask(int id);
	bool containsFetchTask(LFetchTask *task);
	LFetchTask *fetchTaskById(int id);
	void forceUpdate(int id);
	void forceUpdate(LFetchTask *task);
	void forceUpdateAll(UpdateReason reason);
	/* Deprecated */
	LFetchTask *getFetchTaskById(int id);
	bool isProcessing();
	void removeFetchTask(int id);
	void removeFetchTask(LFetchTask *task);
	void startProcessing();
	void stopProcessing();


signals:
	void taskSuccess(int id, LFetchTask* task);
	void taskFailure(int id, LFetchTask* task);

private:
    LDataFetcherPrivate *p;    
};