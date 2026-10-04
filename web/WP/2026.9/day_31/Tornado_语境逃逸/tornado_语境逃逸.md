[靶场地址,点击前往](https://portswigger.net/web-security/server-side-template-injection/exploiting/lab-server-side-template-injection-basic-code-context)

**Burp_py\URL编码\url_encode.py**

*斜体* ~~删除线~~
分隔线
换行用<br>或者在行尾多打两个空格再回车
---

### 新知识
1. Tornado和Python
    - Tornado是 Python的 web框架,和 erb坐一桌,<br>
    它是一个引擎模板,用于在服务端把数据填进 html
2. 关于格式化
    - 有返回值用 {{  }}, 如本题的 1+1, os.system()
    - 无返回值用 {%  %}, 如本题的 import os
---

### 进入靶场
1. 我最开始尝试的是: {{print("test123")}}  -> 图1  
   但是出现报错 -> 图2  
2. 随后我又试了 {{1+1}} -> 图3  
   同样的位置,因为 url编码的缘故,依旧报错  
   url编码之后,问题解决 -> 图4
   - 本题的正常构造应该是 }}{{}},前面的 *}}* 用于截断
3. 本题构造是: **}}{%import os%}{{os.system("rm /home/carlos/morale.txt")}}**  
   url编码之后直接发就行了  -> 图5
   - 我原本有两条评论 -> 删除两次,第二次没得删了会报错
   solved
