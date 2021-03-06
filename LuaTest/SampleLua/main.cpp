// SampleLua.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "lua_tinker.h"

#define export_lua

export_lua class TestClass
{
public:
    export_lua int SUBCPP(int value1, int value2)
    {
        return value1 - value2;
    }

    export_lua void TestPrint()
    {
        printf("hello lua\n");
    }
};

TestClass g_test;

TestClass* get_TestClass_ptr()
{
    return &g_test;
}

void show_error(const char* error)
{
    printf("_ALERT -> %s\n", error);
}

int main()
{
    // 루아 초기화
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    lua_tinker::init(L);


    // 루아에서 호출할 c++ 함수
    lua_tinker::def(L, "get_TestClass_ptr", &get_TestClass_ptr);
    lua_tinker::class_add<TestClass>(L, "TestClass", true);
    lua_tinker::class_def<TestClass>(L, "TestPrint", &TestClass::TestPrint);
    lua_tinker::class_def<TestClass>(L, "SUBCPP", lua_tinker::args_type_overload_member_functor(lua_tinker::make_member_functor_ptr((int(TestClass::*)(int, int))(&TestClass::SUBCPP))));

    lua_tinker::def(L, "_ALERT", show_error);

    // 루아 파일 로드
    lua_tinker::dofile(L, "sample.lua");

    // 루아 함수 호출
    int result = lua_tinker::call<int>(L, "SUMLUA", 100, 200);
    printf("SUMLUA(value1, value2) = %d\n", result);

    // 루아 닫기
    lua_close(L);

    return 0;
}

