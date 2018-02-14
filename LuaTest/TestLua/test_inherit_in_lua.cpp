#include "stdafx.h"
#include "lua_tinker.h"
#include"test.h"
extern std::map<std::string, std::function<bool()> > g_test_func_set;

void test_inherit_in_lua(lua_State* L)
{
	g_test_func_set["test_lua_inhert_lua"] = [L]()->bool
	{
		std::string luabuf =
			R"( lua_create_class("ff_inlua","ff")
				function ff_inlua:test(x)
				   return self:getVal() + x;
				end
				function test_lua_inhert_lua()
					local local_ff = ff_inlua(1);
					return local_ff:test(3) == (1+3);
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());

		lua_gc(L, LUA_GCCOLLECT, 0);
		int nOldCount = ff::s_ref;
		bool bResult = lua_tinker::call<bool>(L, "test_lua_inhert_lua");
		int nCount = ff::s_ref;
		lua_gc(L, LUA_GCCOLLECT, 0);
		nCount = ff::s_ref;
		return (nCount == nOldCount) && bResult;
	};

	g_test_func_set["test_lua_inhert_lua1"] = [L]()->bool
	{
		std::string luabuf =
			R"( lua_create_class("ff_inlua2","ff")

										function test_lua_inhert_lua1()
					local local_ff = ff_inlua2(1);
					return true;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());

		lua_gc(L, LUA_GCCOLLECT, 0);
		int nOldCount = ff::s_ref;
		bool bResult = lua_tinker::call<bool>(L, "test_lua_inhert_lua1");
		int nCount = ff::s_ref;
		lua_gc(L, LUA_GCCOLLECT, 0);
		nCount = ff::s_ref;
		return (nCount == nOldCount) && bResult;
	};
}