-- cpp에서 함수 호출
ocal pTestClass = get_TestClass_ptr();
result = pTestClass:SUBCPP(1, 2);
print("SUBCPP(1,2) = ", result);

-- 일반적인 lua 함수를 선언한다.
function SUMLUA(arg1, arg2)
	return arg1 + arg2
end
