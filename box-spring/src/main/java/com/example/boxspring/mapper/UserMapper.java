package com.example.boxspring.mapper;

import com.example.boxspring.pojo.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.ResultMap;
import org.apache.ibatis.annotations.Select;

import java.util.List;

@Mapper
public interface UserMapper {
    @Select("select * from Web3User")
    List<User> findAll();

    @Select("select * from Web3User where username = #{username} and password = #{password}")
    User login(@Param("username") String username, @Param("password") String password);

    @Select("select * from web3user where id = #{id}")
    User getById(@Param("id") Integer id);

    @Select("select privateKey from web3credentials where Address = #{ads}")
    String getKey(@Param("ads") String ads);
}
