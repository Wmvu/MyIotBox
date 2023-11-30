package com.example.boxspring.utils;

import cn.hutool.core.date.DateUtil;
import cn.hutool.core.util.StrUtil;
import com.auth0.jwt.JWT;
import com.auth0.jwt.algorithms.Algorithm;
import com.example.boxspring.mapper.UserMapper;
import com.example.boxspring.pojo.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import javax.annotation.PostConstruct;
import javax.servlet.http.HttpServletRequest;
import java.util.Date;

@Component
public class TokenUtils {

    private static UserMapper staticUserService;

    @Autowired
    private UserMapper userService;

    @PostConstruct
    public void setUesrService(){
        staticUserService = userService;
    }
    public static String getToken(String userId,String sign){
        return JWT.create().withAudience(userId)
                .withExpiresAt(DateUtil.offsetHour(new Date(),2))
                .sign(Algorithm.HMAC256(sign));
    }
    public static User getCurrentUser(){
        try {
            HttpServletRequest request = ((ServletRequestAttributes) RequestContextHolder.getRequestAttributes()).getRequest();
            String Token = request.getHeader("token");
            if (!StrUtil.isBlank(Token)){
                String and = JWT.decode(Token).getAudience().get(0);
                return staticUserService.getById(Integer.valueOf(and));
            }
        }catch (Exception e){

        }
        return null;
    }
}
