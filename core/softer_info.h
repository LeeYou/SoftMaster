#ifndef SOFTER_INFO_H_
#define SOFTER_INFO_H_


struct SofterInfo{
public:
	std::wstring name_;
	std::wstring file_path_;
	std::wstring file_version_;
	std::wstring file_discript;

	bool Equals(const SofterInfo& data) {
		return name_ == data.name_ &&
			file_path_ == data.file_path_&&
			file_version_ == data.file_version_ &&
			file_discript == data.file_discript;
	}
};

#endif