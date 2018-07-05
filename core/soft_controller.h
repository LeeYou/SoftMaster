#ifndef SOFT_CONTROLLER_H_
#define SOFT_CONTROLLER_H_

class BaseSoft;

class SoftController {
public:
	virtual void ChangeSoft(BaseSoft *soft) = 0;
	virtual void DeleteSoft(BaseSoft * soft) = 0;
	virtual bool DownloadSoft(BaseSoft *soft) = 0;

protected:
	virtual ~SoftController() {}
};

#endif
