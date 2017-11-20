#pragma once
#include <CGE.h>
#include <string>
#include <vector>
#include <memory>
class menuScene:public cge::Scene
{
private:
	std::vector<std::string> _mods;
	bool _haveGotTarget;
	std::string _targetMod;
	size_t _curPage, _maxPage, _cursor;
	bool selectUp();
	bool selectDown();
	bool previousPage();
	bool nextPage();
public:
	template<class... Ts>
	static std::shared_ptr<menuScene> create(Ts&&... args)
	{
		initCheck();
		return std::shared_ptr<menuScene>(new menuScene(std::forward<Ts>(args)...));
	}
	virtual void init();
	virtual void update();
	bool haveGotTarget() {return _haveGotTarget;}
	std::string getTargetMod() { return _targetMod; }
};