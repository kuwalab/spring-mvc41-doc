= リクエスト

== リクエストのいろいろな受け取り方

==={002} GETパラメータを受け取る

@<b>{タグ【002】}

通常のGETパラメータを受け取るには、@<tt>{@RequestParam}アノテーションを使用します。

//list[002-C002Controller.java][C002Controller.java]{
package com.example.spring.controller.c002;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/c002")
public class C002Controller {
    @RequestMapping(value = "/getParam")
    public String getParam(@RequestParam String foo, @RequestParam String bar,
            Model model) {
        model.addAttribute("modelFoo", foo);
        model.addAttribute("modelBar", bar);
        return "c002/getParam";
    }

    @RequestMapping(value = "/getParam2")
    public String getparam2(@RequestParam("foo1") String foo,
            @RequestParam("bar1") String bar, Model model) {
        model.addAttribute("modelFoo", foo);
        model.addAttribute("modelBar", bar);
        return "c002/getParam";
    }

    @RequestMapping("/getParam3")
    public String getParam3(@RequestParam(required = false) String foo,
            @RequestParam(defaultValue = "default") String bar, Model model) {
        model.addAttribute("foo", foo);
        model.addAttribute("bar", bar);
        return "c002/getParam";
    }
}
//}

上記の例だと、/getParam?foo=1&bar=2や、/getParam2?foo1=3&bar1=4といったリクエストを投げます。

@<tt>{@RequestParam}もパラメータの名前とメソッドの引数の名前が同じものが自動で割り当てられます。パラメータの名前が違う場合には、@<tt>{@RequestParam}の属性でその名前を指定します。

@<tt>{@RequestParam}で指定したパラメータがない場合、例えば、/getParamというリクエストが送信された場合、必要なパラメータが無いため例外が発生します。

パラメータを必須としない場合には、required属性をfalseにするか、default属性を設定します。default属性を設定するとrequred属性は暗黙的にfalseになります。

@PathVariableと違い、リクエストスコープに自動で割り当てられることはないため、modelを介してJSPにデータを渡しています。

表示用のgetParam.jspは以下のようになります。

//list[002-getParam.jsp][getParam.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
fooの値は <c:out value="${foo}" /><br>
barの値は <c:out value="${bar}" /><br>
modelFooの値は <c:out value="${modelFoo}" /><br>
modelBarの値は <c:out value="${modelBar}" />
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[002-C002ControllerTest.java][C002ControllerTest.java]{
package com.example.spring.controller.c002;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C002ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void getParam_foo$abc_bar$123のGET() throws Exception {
        mockMvc.perform(get("/c002/getParam?foo=abc&bar=123"))
                .andExpect(status().isOk())
                .andExpect(view().name("c002/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("modelFoo", is("abc")))
                .andExpect(model().attribute("modelBar", is("123")))
                .andExpect(request().attribute("foo", is(nullValue())))
                .andExpect(request().attribute("bar", is(nullValue())));
    }

    @Test
    public void getParam_foo$abcのGET_パラメータ不足によるエラー() throws Exception {
        mockMvc.perform(get("/c002/getParam?foo=abc")).andExpect(
                status().isBadRequest());
    }

    @Test
    public void getParam2_foo1$abc_bar1$123のGET() throws Exception {
        mockMvc.perform(get("/c002/getParam2?foo1=abc&bar1=123"))
                .andExpect(status().isOk())
                .andExpect(view().name("c002/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("modelFoo", is("abc")))
                .andExpect(model().attribute("modelBar", is("123")))
                .andExpect(request().attribute("foo1", is(nullValue())))
                .andExpect(request().attribute("bar1", is(nullValue())));
    }

    @Test
    public void getParam3_foo$abc_bar$123のGET() throws Exception {
        mockMvc.perform(get("/c002/getParam3?foo=abc&bar=123"))
                .andExpect(status().isOk())
                .andExpect(view().name("c002/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("foo", is("abc")))
                .andExpect(model().attribute("bar", is("123")));
    }

    @Test
    public void getParam3のGET() throws Exception {
        mockMvc.perform(get("/c002/getParam3")).andExpect(status().isOk())
                .andExpect(view().name("c002/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("foo", is(nullValue())))
                .andExpect(model().attribute("bar", is("default")));
    }
}
//}

==={003} GETパラメータを受け取る（Optional）

@<b>{タグ【003】}

Spring MVC 4.1から@RequestParamのパラメータにOptionalが使用できるようになりました。Optionalを使用することで、事実上パラメータは必須ではなくなります。例えば、fooパラメータを設定した場合を例にします。Stringで受けた場合にはfooパラメータが、ない場合にはメソッドが呼ばれません。対してOptionalにした場合にはメソッドが呼び出されます。次の例で確認します。

//list[003-C003Controller.java][C003Controller.java]{
package com.example.spring.controller.c003;

import java.util.Optional;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
@RequestMapping("/c003")
public class C003Controller {
    @RequestMapping(value = "/getParam")
    public String getParam(@RequestParam Optional<String> foo,
            @RequestParam Optional<Integer> bar, Model model) {
        model.addAttribute("modelFoo", foo.orElse("nullです"));
        model.addAttribute("modelBar", bar.orElse(-9999));
        return "c003/getParam";
    }
}
//}

この例の場合には、Optional#orElseメソッドを使用してデフォルト値を設定しています。fooやbarパラメータが指定されなかった場合には、デフォルト値（orElse）が使用されます。

JSPは特別なことはありません。

//list[003-getParam.jsp][getParam.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
fooの値は <c:out value="${foo}" /><br>
barの値は <c:out value="${bar}" /><br>
modelFooの値は <c:out value="${modelFoo}" /><br>
modelBarの値は <c:out value="${modelBar}" />
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[003-C003ControllerTest.java][C003ControllerTest.java]{
package com.example.spring.controller.c003;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C003ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void getParam_foo$abc_bar$123のGET() throws Exception {
        mockMvc.perform(get("/c003/getParam?foo=abc&bar=123"))
                .andExpect(status().isOk())
                .andExpect(view().name("c003/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("modelFoo", is("abc")))
                .andExpect(model().attribute("modelBar", is(123)))
                .andExpect(request().attribute("foo", is(nullValue())))
                .andExpect(request().attribute("bar", is(nullValue())));
    }

    @Test
    public void getParam_foo$null_bar$nullのGET() throws Exception {
        mockMvc.perform(get("/c003/getParam")).andExpect(status().isOk())
                .andExpect(view().name("c003/getParam"))
                .andExpect(model().hasNoErrors())
                .andExpect(model().attribute("modelFoo", is("nullです")))
                .andExpect(model().attribute("modelBar", is(-9999)))
                .andExpect(request().attribute("foo", is(nullValue())))
                .andExpect(request().attribute("bar", is(nullValue())));
    }
}
//}

==={004} URLの一部をパラメータとして受け取る

@<b>{タグ【004】}

リクエストされるURLの一部、例えば/hoge/fooというアクセスのfooの値をパラメータとして受け取る場合には、@PathVariableアノテーションを使って受け取ることができます。

//list[004-C004Controller.java][C004Controller.java]{
package com.example.spring.controller.c004;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping("/c004")
public class C004Controller {
    @RequestMapping(value = "/pathVar1/{var}", method = RequestMethod.GET)
    public String pathVar(@PathVariable String var) {
        return "c004/pathVar";
    }

    @RequestMapping(value = "/pathVar2/{var1}", method = RequestMethod.GET)
    public String pathVar2(@PathVariable("var1") String var) {
        return "c004/pathVar";
    }
}
//}

パラメータは{}で指定し、その中の名称がパラメータ名となります。受け取るパラメータはメソッドの引数で@PathVariableアノテーションを付けて指定します。この時パラメータ名と変数名が同じ場合には何も指定は必要ありません。pathVar2メソッドのようにパラメータ名と変数名が異なる場合には、アノテーションの属性としてパラメータ名が必要になります。

表示用のJSPは次のようになります。@PathVariableで指定されたパラメータは、Spring MVCによって自動的にリクエストスコープの同名の属性に割り当てられます。そのため、JSP側ではリクエストスコープから値を持ってくるため、コントローラでは何もしていません。

//list[004-pathVar.jsp][pathVar.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
varの値は <c:out value="${var}" /><br>
var1の値は <c:out value="${var1}" />
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[004-C004ControllerTest.java][C004ControllerTest.java]{
package com.example.spring.controller.c004;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C004ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void pathVar_12345へのGET() throws Exception {
        mockMvc.perform(get("/c004/pathVar1/12345")).andExpect(status().isOk())
                .andExpect(view().name("c004/pathVar"))
                .andExpect(request().attribute("var", is("12345")));
    }

    @Test
    public void pathVar2_abcdeへのGET() throws Exception {
        mockMvc.perform(get("/c004/pathVar2/abcde")).andExpect(status().isOk())
                .andExpect(view().name("c004/pathVar"))
                .andExpect(request().attribute("var1", is("abcde")));
    }
}
//}

==={005} URLの一部をパラメータとして受け取る（複数パラメータ）

@<b>{タグ【005】}

URLをパラメータとする場合、そのパラメータは1つでなくても構いません。複数のパラメータを受け取ることができますし、パラメータとパラメータの間にURLの一部が混ざっていても問題ありません。

具体的なサンプルは以下のとおりです。

//list[005-C005Controller.java][C005Controller.java]{
package com.example.spring.controller.c005;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping("/c005")
public class C005Controller {
    @RequestMapping(value = "/pathVar1/{foo}/{bar}", method = RequestMethod.GET)
    public String pathVar3(@PathVariable String foo, @PathVariable String bar) {
        return "c005/pathVar";
    }

    @RequestMapping(value = "/pathVar2/{bar1}/{foo1}", method = RequestMethod.GET)
    public String pathVar4(@PathVariable("bar1") String bar,
            @PathVariable("foo1") String foo) {
        return "c005/pathVar";
    }

    @RequestMapping(value = "/pathVar3/{foo}/param/{bar}", method = RequestMethod.GET)
    public String pathVar5(@PathVariable String foo, @PathVariable String bar) {
        return "c005/pathVar";
    }
}
//}

2つ目のurlpara4メソッドではパラメータの順番と受け取るメソッドの引数の順番を変えています。3つ目のurlparam5メソッドでは、fooパラメータとbarパラメータの間にリテラルのパスを含んでいます。

このように、柔軟にパラメータの設定ができます。

最後に表示用のpathVar.jspは以下になります。

//list[005-pathVar.jsp][pathVar.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
fooの値は <c:out value="${foo}" /><br>
barの値は <c:out value="${bar}" /><br>
foo1の値は <c:out value="${foo1}" /><br>
bar1の値は <c:out value="${bar1}" />
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[005-C005ControllerTest.java][C005Controller.java]{
package com.example.spring.controller.c005;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C005ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void pathVar1_123_abcへのGET() throws Exception {
        mockMvc.perform(get("/c005/pathVar1/123/abc"))
                .andExpect(status().isOk())
                .andExpect(view().name("c005/pathVar"))
                .andExpect(request().attribute("foo", is("123")))
                .andExpect(request().attribute("bar", is("abc")));
    }

    @Test
    public void pathVar2_123_abcへのGET() throws Exception {
        mockMvc.perform(get("/c005/pathVar2/123/abc"))
                .andExpect(status().isOk())
                .andExpect(view().name("c005/pathVar"))
                .andExpect(request().attribute("bar1", is("123")))
                .andExpect(request().attribute("foo1", is("abc")));
    }

    @Test
    public void pathVar3_123_param_abcへのGET() throws Exception {
        mockMvc.perform(get("/c005/pathVar3/123/param/abc"))
                .andExpect(status().isOk())
                .andExpect(view().name("c005/pathVar"))
                .andExpect(request().attribute("foo", is("123")))
                .andExpect(request().attribute("bar", is("abc")));
    }
}
//}

==={006} リクエストボディをそのまま受け取る

@<b>{タグ【006】}

POSTリクエストのデータは、GETリクエストと同様に@RequestParamで受け取ることもできますが、リクエストボディの生データをそのまま受け取ることもできます。

//list[006-C006Controller.java][C006Controller.java]{
package com.example.spring.controller.c006;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
@RequestMapping("/c006")
public class C006Controller {
    @RequestMapping("/bodyForm")
    public String bodyForm() {
        return "c006/bodyForm";
    }

    @RequestMapping(value = "/bodyRecv", method = RequestMethod.POST)
    public String bodyRecv(@RequestBody String body, Model model) {
        model.addAttribute("body", body);
        return "c006/bodyRecv";
    }
}
//}

リクエストボディは、@RequestBodyアノテーションを付けた引数で受け取ります。今回の場合だとリクエストボディがそのままStringのbodyに入ります。

RequestBodyも必須かどうかはrequired属性で指定できます。

POSTデータ送信用のJSP、bodyForm.jspです。

//list[006-bodyForm.jsp][bodyForm.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <form action="bodyRecv" method="post">
   名前: <input type="text" name="name" size="20"><br>
   年齢: <input type="text" name="age" size="20"><br>
   <input type="submit" value="送信">
  </form>
 </body>
</html>
//}

リクエストボディ表示用のbodyRecv.jspです。

//list[006-bodyRecv.jsp][bodyRecv.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
nameの値は <c:out value="${name}" /><br>
ageの値は <c:out value="${age}" /><br>
bodyの値は <c:out value="${body}" /><br>
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[006-C006ControllerTest.java][C006ControllerTest.java]{
package com.example.spring.controller.c006;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C006ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void bodyFormのGET() throws Exception {
        mockMvc.perform(get("/c006/bodyForm")).andExpect(status().isOk())
                .andExpect(view().name("c006/bodyForm"));
    }

    @Test
    public void bodyRecvのPOST() throws Exception {
        mockMvc.perform(post("/c006/bodyRecv").content("name=test&age=33"))
                .andExpect(status().isOk())
                .andExpect(view().name("c006/bodyRecv"))
                .andExpect(model().attributeExists("body"))
                .andExpect(model().attribute("body", is("name=test&age=33")))
                .andExpect(model().attributeDoesNotExist("name", "age"));
    }
}
//}

==={007} GETパラメータを受け取る

@<b>{タグ【007】}

今回はHttpServletRequestとSpringで用意されている、Reqeustのようなクラスです。WebRequestは色々便利に使えますが、今回はHttpServletRequestと同じ動きができるというところだけ確認します。

//list[007-C007Controller.java][C007Controller.java]{
package com.example.spring.controller.c007;

import javax.servlet.http.HttpServletRequest;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.context.request.NativeWebRequest;
import org.springframework.web.context.request.WebRequest;

@Controller
@RequestMapping("/c007")
public class C007Controller {
    @RequestMapping("/req")
    public String req(HttpServletRequest request, Model model) {
        model.addAttribute("foo", request.getParameter("foo"));
        return "c007/req";
    }

    @RequestMapping("/req2")
    public String req2(WebRequest request, Model model) {
        model.addAttribute("foo", request.getParameter("foo"));
        return "c007/req";
    }

    @RequestMapping("/req3")
    public String req3(NativeWebRequest request, Model model) {
        model.addAttribute("foo", request.getParameter("foo"));
        return "c007/req";
    }
}
//}

req.jspは以下です。

//list[006-req.jsp][req.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
fooの値は <c:out value="${foo}" /><br>
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[006-C006ControllerTest.java][C006ControllerTest.java]{
package com.example.spring.controller.c007;

import static org.hamcrest.CoreMatchers.*;
import static org.springframework.test.web.servlet.request.MockMvcRequestBuilders.*;
import static org.springframework.test.web.servlet.result.MockMvcResultMatchers.*;
import static org.springframework.test.web.servlet.setup.MockMvcBuilders.*;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.web.context.WebApplicationContext;

@RunWith(SpringJUnit4ClassRunner.class)
@WebAppConfiguration
@ContextConfiguration(locations = {
    "file:src/main/webapp/WEB-INF/spring/spring-context.xml" })
public class C007ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void reqのGET() throws Exception {
        mockMvc.perform(get("/c007/req").param("foo", "foo"))
                .andExpect(status().isOk()).andExpect(view().name("c007/req"))
                .andExpect(model().hasNoErrors())
                .andExpect(request().attribute("foo", is("foo")));
    }

    @Test
    public void req2のGET() throws Exception {
        mockMvc.perform(get("/c007/req2").param("foo", "foo"))
                .andExpect(status().isOk()).andExpect(view().name("c007/req"))
                .andExpect(model().hasNoErrors())
                .andExpect(request().attribute("foo", is("foo")));
    }

    @Test
    public void req3のGET() throws Exception {
        mockMvc.perform(get("/c007/req3").param("foo", "foo"))
                .andExpect(status().isOk()).andExpect(view().name("c007/req"))
                .andExpect(model().hasNoErrors())
                .andExpect(request().attribute("foo", is("foo")));
    }
}
//}


