# [靶场地址](https://portswigger.net/web-security/ssrf/blind/lab-out-of-band-detection)

### 关于本题
1. 在本题中,读取&解析请求的Referer和服务器获取URL是异步执行的  
   获取结构不会返回到页面  
   - 异步: 两条流水线,各干各的
   - 如果想要获取返回结果,需要使用自己的域名进行OOB带外交互
---

### 进入靶场
1. 找到请求的 Referer,改成自己的Collaborator　　-> 图1.图2

**solved**