#ifndef BASE_SOFT_H_
#define BASE_SOFT_H_

#include "softer_info.h"

class SoftController;
class BaseSoft{
public:
	explicit BaseSoft(SoftController *controller);
	~BaseSoft();

	void SetData(const SofterInfo &data);
	const SofterInfo& data() const { return data_; }

	void set_downloading(bool downloading) { downloading_ = downloading; }
	bool downloading() const { return downloading_; }

	void set_new_version(const std::wstring &ver);
	bool is_update() const ;

	SoftController* controller() const { return controller_; }

private:
	SoftController* controller_;
	SofterInfo data_;
	bool downloading_;
	std::wstring new_version_;

	DISALLOW_COPY_AND_ASSIGN(BaseSoft);
};

#endif