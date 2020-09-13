namespace LLog {
	void setModuleName(const char *name);
	void logw(const char *fmt, ...);
	void logd(const char *fmt, ...);
	void loge(const char *fmt, ...);
	void logf(const char *fmt, ...);
	void logi(const char *fmt, ...);
	void logv(const char *fmt, ...);
}