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


