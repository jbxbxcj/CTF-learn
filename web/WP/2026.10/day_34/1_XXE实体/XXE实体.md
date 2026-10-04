# [靶场地址](https://portswigger.net/web-security/xxe/lab-exploiting-xxe-to-retrieve-files)

## 关于本题
1. 实体在 *sum/OOB指令合集* 里面有所提及
```
<! DOCTYPE message[
    <!ENTITY greeting "hello world">
]>
<message>&greeting;</message>
```
   - XML　->　一种"有结构的文本数据格式"
   - DTD　->　XML的规则/声明区
   - <!DOCTYPE message[　声明此XML的DTD
   - message　是声明的*根元素*
   - <!ENTITY greeting "hello world">　声明一个名为*greeting*的实体,其值为普通文本
   - <message></message>　普通XML元素,类似html的标签
   - &greeting;　实体引用,解析器会把它当作是"hello world"

2. 外部实体读取文件的操作:
```
<!ENTITY a_good_name SYSTEM "资源路径">
&a_good_name;
```
   - SYSTEM　表示实体值来自外部系统标识符,而非引号的固定文本 
---

### 进入靶场
1. 我是先尝试使用上面的那个message,然后发现有了两个根元素
两个根元素就开始报错了　　->　图1
2. 然后我把message换成了本题的*stockCheck*,回传成功　　->　图2
3. 然后使用<!ENTITY emmm system "/ect/passwd">
查看成功　　->　图3  
*solved*
---

## 修复
1. 根因: 服务端XML解析接收客户端的*DOCTYPE*,且允许解析外部实体
2. 在服务端禁用实体解析,*含有DOCTYPE的请求一律拒绝*
3. response报错回显不应该显示具体信息