#pragma once

class CCEHttp
{
public:
	CCEHttp(void);
	~CCEHttp(void);
	// 初始化
	void OnInit(void);
	// 连接服务器
	bool ConnectServer(void);
};
