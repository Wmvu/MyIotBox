package com.example.boxspring.controller;

import com.example.boxspring.controller.intercpor.Result;
import com.example.boxspring.mapper.UserMapper;
import com.example.boxspring.pojo.User;
import com.example.boxspring.utils.TokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
public class wen {
    @Autowired
    UserMapper userMapper;
    @GetMapping("/aaa")
    public String aaa(){
        System.out.println(userMapper.findAll());
        return " ";
    }
    @GetMapping("/login")
    public String login(@RequestParam String username,@RequestParam String password){

        return userMapper.login(username,password).toString();
    }
    @PostMapping("/login")
    public Result login(@RequestBody User user){
        User user1 = userMapper.login(user.getUsername(),user.getPassword());
        if(user1 != null){
            System.out.println("登入成功");

            String Token = TokenUtils.getToken(user1.getId().toString(),user1.getPassword());
            user.setWeb3user(user1.getWeb3user());
            user.setToken(Token);
            return Result.success(user);
        }else{
            return Result.error("200","登入失败");
        }

    }
}
