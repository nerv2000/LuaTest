-- cpp���� �Լ� ȣ��
ocal pTestClass = get_TestClass_ptr();
result = pTestClass:SUBCPP(1, 2);
print("SUBCPP(1,2) = ", result);

-- �Ϲ����� lua �Լ��� �����Ѵ�.
function SUMLUA(arg1, arg2)
	return arg1 + arg2
end
