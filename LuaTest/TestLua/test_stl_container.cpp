#include "stdafx.h"
#include "lua_tinker.h"
#include"test.h"
extern std::map<std::string, std::function<bool()> > g_test_func_set;




std::unordered_map<int, int> g_testhashmap = { { 1,1 },{ 3,2 },{ 5,3 },{ 7,4 } };
std::unordered_map<int, int> push_hashmap()
{
	return g_testhashmap;
}

std::map<int, int> g_testmap = { { 1,1 },{ 3,2 },{ 5,3 },{ 7,4 } };
std::map<int, int> push_map()
{
	return g_testmap;
}
const std::map<int, int>& push_map_ref()
{
	return g_testmap;
}

std::set<int> g_testset = { 1,2,3,4,5 };
std::set<int> push_set()
{
	return g_testset;
}


std::vector<int> g_testvec = { 1,2,3,4,5 };
std::vector<int> push_vector()
{
	return g_testvec;
}

const std::vector<int>& push_vector_const()
{
	return g_testvec;
}

std::string vector_join_const(const std::vector<int>& vec, const std::string& sep)
{
	std::string result;
	for(auto v : vec)
	{
		if(result.empty() == false)
			result+=sep;
		result += std::to_string(v);
	}
	return result;
}


void test_stl_container(lua_State* L)
{



	g_test_func_set["test_lua_map"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_map()
					local map_table = push_map();
					return map_table;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::map<int, int> mapval = lua_tinker::call<decltype(mapval)>(L, "test_lua_map");
		if (mapval.empty())
			return false;
		for (const auto& v : g_testmap)
		{
			if (mapval[v.first] != v.second)
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_map_2"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_map_2()
					local map_table = push_map_ref();
					local pTest = TestCon();
					pTest:ChangeDataMapRef(map_table);
					return pTest:getDataMap();
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::map<int, int> mapval = lua_tinker::call<decltype(mapval)>(L, "test_lua_map_2");
		if (mapval.empty())
			return false;
		for (const auto& v : g_testmap)
		{
			if (mapval[v.first] != v.second)
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_map_3"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_map_3()
					local map_table = push_map(); --map to lua_table
					local pTest = TestCon();
					local pTest2 = TestCon();
					pTest:ChangeDataMap(map_table);	--lua_table to map
					pTest2:ChangeDataMapPtr(pTest:getDataMapPtr());
					return pTest2:getDataMapRef();		--map to lua_table then pop as a map
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		const std::map<int, int>& mapval = lua_tinker::call<decltype(mapval)>(L, "test_lua_map_3");
		if (mapval.empty())
			return false;
		for (const auto& v : g_testmap)
		{
			auto itfind = mapval.find(v.first);
			if(itfind != mapval.end())
			if (itfind->second != v.second)
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_map_4"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_map_4()
					local map_table = push_map();
					local pTest = TestCon();
					local pTest2 = TestCon();
					pTest:ChangeDataMap(map_table);
					pTest2:ChangeDataMap(pTest:getDataMapRef());
					return pTest2:getDataMapRef();		
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		const std::map<int, int>* pMap = lua_tinker::call<decltype(pMap) >(L, "test_lua_map_4");
		if (pMap == nullptr)
			return false;

		std::map<int, int> mapval = *pMap;
		if (mapval.empty())
			return false;
		for (const auto& v : g_testmap)
		{
			if (mapval[v.first] != v.second)
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_hashmap"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_hashmap()
					local map_table = push_hashmap();
					return map_table;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::map<int, int> mapval = lua_tinker::call<decltype(mapval)>(L, "test_lua_hashmap");
		for (const auto& v : g_testhashmap)
		{
			if (mapval[v.first] != v.second)
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_set"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_set()
					local testSet = push_set();
					return testSet;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::vector<int> val = lua_tinker::call<decltype(val)>(L, "test_lua_set");
		if (val.empty())
			return false;
		for (const auto& v : val)
		{
			if (g_testset.find(v) == g_testset.end())
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_set_2"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_set_2()
					local testSet = push_set();
					local pTest = TestCon();
					pTest:ChangeDataSet(testSet);
					return pTest:getDataSet();
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::vector<int> val = lua_tinker::call<decltype(val)>(L, "test_lua_set_2");
		if (val.empty())
			return false;
		for (const auto& v : val)
		{
			if (g_testset.find(v) == g_testset.end())
				return false;
		}
		return true;
	};
	g_test_func_set["test_lua_set_3"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_set_3()
					local testSet = push_set();
					local pTest = TestCon();
					local pTest2 = TestCon();
					pTest:ChangeDataSet(testSet);
					pTest2:ChangeDataSetRef(pTest:getDataSetRef());
					return pTest2:getDataSet();
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::vector<int> val = lua_tinker::call<decltype(val)>(L, "test_lua_set_3");
		if (val.empty())
			return false;
		for (const auto& v : val)
		{
			if (g_testset.find(v) == g_testset.end())
				return false;
		}
		return true;
	};

	g_test_func_set["test_lua_vec"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_vec()
					local testSet = push_vector();
					return testSet;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::vector<int> val = lua_tinker::call<decltype(val)>(L, "test_lua_vec");
		if (val.empty())
			return false;
		for (size_t i = 0; i < g_testvec.size(); i++)
		{
			if (g_testvec[i] != val[i])
				return false;
		}
		return true;
	};
	
	g_test_func_set["test_lua_vec1"] = [L]()->bool
	{
		std::string luabuf =
			R"(function test_lua_vec1()
					local testSet = push_vector_const();
					local str = vector_join_const(testSet,",");
					return str;
				end
			)";
		lua_tinker::dostring(L, luabuf.c_str());
		std::string val = lua_tinker::call<decltype(val)>(L, "test_lua_vec1");
		
		return val == "1,2,3,4,5";
	};

}