= レスポンス

== ファイルのダウンロード

==={022} CSVファイルのダウンロード（Springに依存しない方法）

@<b>{タグ【022】}

今回はCSVダウンロードです。ダウンロードにはいくつか方法があるのですが、今回はSpringにあまり依存しない方法を紹介します。

具体的なソースは以下のなります。csvInitでアンカーの書かれた画面を開き、csvDownが実際のダウンロードになります。ダウンロードの際には戻り値はvoidとして、HttpServletResponse#getWirter()メソッドでダウンロードするデータを書き出します。

//list[022-C022Controller.java][C022Controller.java]{
package com.example.spring.controller.c022;

import java.io.IOException;
import java.io.PrintWriter;

import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.util.MimeTypeUtils;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class C022Controller {
    @RequestMapping("/c022/csvInit")
    public String csvInit() {
        return "c022/csvInit";
    }

    @RequestMapping("/c022/csvDown")
    public void csvDown(HttpServletResponse response) {
        response.setContentType(MimeTypeUtils.APPLICATION_OCTET_STREAM_VALUE
                + ";charset=utf-8");
        response.setHeader("Content-Disposition",
                "attachment; filename=\"test.csv\"");
        try (PrintWriter pw = response.getWriter()) {
            pw.print("山田　太郎,33\r\n");
            pw.print("田中　花子,29\r\n");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
//}

アンカーを表示する画面です。単純なアンカーのみです。

//list[022-csvInit.jsp][csvInit.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <a href="csvDown">csvDown</a>
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[022-C022ControllerTest.java][C022ControllerTest.java]{
package com.example.spring.controller.c022;

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
public class C022ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void csvInitのGET() throws Exception {
        mockMvc.perform(get("/c022/csvInit")).andExpect(status().isOk())
                .andExpect(view().name("c022/csvInit"));
    }

    @Test
    public void csvDownのGET() throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append("山田　太郎,33\r\n");
        sb.append("田中　花子,29\r\n");
        mockMvc.perform(get("/c022/csvDown"))
                .andExpect(status().isOk())
                .andExpect(
                        content().contentType(
                                "application/octet-stream;charset=utf-8"))
                .andExpect(content().string(sb.toString()));
    }
}
//}

==={023} CSVファイルのダウンロード（ResponseEntity）

@<b>{タグ【023】}

今回もCSVダウンロードについてです。今回はResponseEntityクラスを使用したダウンロードについてです。

ResponseEntityではデータと、ヘッダー、ステータスコードを返せます。

日本語の文字化けをしないようにするために、HttpHeadersクラスのsetContentTypeを使わずに、addメソッドで文字コードと一緒にcontent-typeを指定しています。

CSVデータはただの文字列のデータになります。

//list[023-C023Controller.java][C023Controller.java]{
package com.example.spring.controller.c023;

import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Controller;
import org.springframework.util.MimeTypeUtils;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;

@Controller
public class C023Controller {
    @RequestMapping("/c023/csvInit")
    public String csvInit() {
        return "c023/csvInit";
    }

    @RequestMapping(value = "/c023/csvDown", method = RequestMethod.GET,
        produces = "application/octet-stream;charset=utf-8")
    public ResponseEntity<String> csvDown() {
        HttpHeaders headers = new HttpHeaders();
        // headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        headers.add("contet-type", MimeTypeUtils.APPLICATION_OCTET_STREAM_VALUE
                + ";utf-8");
        headers.set("Content-Disposition", "filename=\"test2.csv\"");
        String csvData = "山田　太郎,33\r\n";
        csvData = csvData + "田中　花子,29\r\n";

        return new ResponseEntity<String>(csvData, headers, HttpStatus.OK);
    }
}
//}

アンカーを表示する画面です。単純なアンカーのみです。

//list[023-csvInit.jsp][csvInit.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <a href="csvDown">csvDown</a>
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[023-C023ControllerTest.java][C023ControllerTest.java]{
package com.example.spring.controller.c023;

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
public class C023ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void csvInitのGET() throws Exception {
        mockMvc.perform(get("/c023/csvInit")).andExpect(status().isOk())
                .andExpect(view().name("c023/csvInit"));
    }

    @Test
    public void csvDownのGET() throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append("山田　太郎,33\r\n");
        sb.append("田中　花子,29\r\n");
        mockMvc.perform(get("/c023/csvDown"))
                .andExpect(status().isOk())
                .andExpect(
                        content().contentType(
                                "application/octet-stream;charset=utf-8"))
                .andExpect(content().string(sb.toString()));
    }
}
//}

==={024} CSVファイルのダウンロード（ResponseBody）

@<b>{タグ【024】}

今回もCSVダウンロードについてです。今回はResponseBodyを返す形で実装します。

ResponseEntityではデータと、ヘッダー、ステータスコードを返せます。

日本語の文字化けをしないようにするために、HttpHeadersクラスのsetContentTypeを使わずに、addメソッドで文字コードと一緒にcontent-typeを指定しています。

CSVデータはただの文字列のデータになります。

//list[024-C024Controller.java][C024Controller.java]{
package com.example.spring.controller.c024;

import javax.servlet.http.HttpServletResponse;

import org.springframework.stereotype.Controller;
import org.springframework.util.MimeTypeUtils;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class C024Controller {
    @RequestMapping("/c024/csvInit")
    public String csvInit() {
        return "c024/csvInit";
    }

    @RequestMapping(value = "/c024/csvDown", method = RequestMethod.GET,
            produces = MimeTypeUtils.APPLICATION_OCTET_STREAM_VALUE
            + ";charset=utf-8")
    @ResponseBody
    public String csvDown3(HttpServletResponse response) {
        response.setHeader("Content-Disposition",
                "attachment; filename=\"test3.csv\"");

        String csvData = "山田　太郎,33\r\n";
        csvData = csvData + "田中　花子,29\r\n";
        return csvData;
    }
}
//}

アンカーを表示する画面です。単純なアンカーのみです。

//list[024-csvInit.jsp][csvInit.jsp]{
<%@page contentType="text/html; charset=utf-8" %><%--
--%><!DOCTYPE html>
<html>
 <head>
  <meta charset="utf-8">
  <title>サンプル</title>
 </head>
 <body>
  <a href="csvDown">csvDown</a>
 </body>
</html>
//}

確認用のテストケースは次のとおりです。

//list[024-C024ControllerTest.java][C024ControllerTest.java]{
package com.example.spring.controller.c024;

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
public class C024ControllerTest {
    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        mockMvc = webAppContextSetup(wac).build();
    }

    @Test
    public void csvInitのGET() throws Exception {
        mockMvc.perform(get("/c024/csvInit")).andExpect(status().isOk())
                .andExpect(view().name("c024/csvInit"));
    }

    @Test
    public void csvDownのGET() throws Exception {
        StringBuilder sb = new StringBuilder();
        sb.append("山田　太郎,33\r\n");
        sb.append("田中　花子,29\r\n");
        mockMvc.perform(get("/c024/csvDown"))
                .andExpect(status().isOk())
                .andExpect(
                        content().contentType(
                                "application/octet-stream;charset=utf-8"))
                .andExpect(content().string(sb.toString()));
    }
}
//}

