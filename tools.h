#ifndef TOOLS_H
#define TOOLS_H

#ifdef DEBUG
	#define debug(...) printf(__VA_ARGS__)
#else
	#define debug(...)
#endif

//	任意键继续
void anykey_continue(void);

//	隐藏密码
void coverKey(char ch[]);

#endif//TOOLS_h
