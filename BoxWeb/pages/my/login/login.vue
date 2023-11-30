<template>
	<view>
		<uni-nav-bar v-if="is_password" color="white" leftText="返回" leftIcon="left" shadow :fixed="true" background-color="#007AFF" title="欢迎来到我的平台" height="100rpx" rightText="验证码登录" @clickLeft="bad" @clickRight="vied" ></uni-nav-bar>
		<uni-nav-bar v-if="!is_password" color="white" leftText="返回" leftIcon="left" shadow :fixed="true" background-color="#007AFF" title="欢迎来到我的平台" height="100rpx" rightText="密码登录" @clickLeft="bad" @clickRight="vied" ></uni-nav-bar>
		<view class="back" catchtouchmove="true">
		<view class="login">
			<text style="font-size: 20px; color: #2979FF;">登录</text>
			<input class="tabnumber" v-model="username" type="number" placeholder="请输入手机号" maxlength="11" value="" />
			<input v-if="is_password" v-model="password" class="pasnum" password type="safe-password" placeholder="请输入密码">
			
			<button class="right" type="primary" @click="login()">Login</button>
			<view @click="whatpsd()"><text style="margin-left: 480rpx;color: darkgray;">忘记密码</text></view>
		</view>
	</view>		

	</view>
</template>

<script>
	export default {
		data() {
			return {
				is_password:true,
				username:'',
				password:''
			}
		},
		mounted() {
			// this.to();
			// uni.navigateTo({
			// 	url:'/pages/index/shop/shop'
			// })
			
		},
		methods: {
			bad() {
				uni.navigateBack({
					delta: 1
				})
			},
			vied() {
			this.is_password=!this.is_password
			},
			whatpsd(){
				alert("请联系管理员重置")
			},
			to(){
				uni.switchTab({
					url:'/pages/index/index',
					fail: (re) => {
						console.log(re)
					}
				})
			},
			login(){
				const baseurl = "http://127.0.0.1:8080/"
				uni.request({
					url:'http://localhost:8080/login',
					method:'POST',
					data:{
						username:this.username,
						password:this.password
					},
					success: (res) => {
						console.log(res.data.code)
						if(res.data.code !== '200'){
							uni.showToast({
								icon:"none",
								title:res.data.msg,
								duration: 2000
							});
							
							// uni.showLoading({
							// 	title:"加载中"
							// })
							// uni.getUserProfile({
							// 	desc:"dqwe",
							// 	success: async () => {
									
							// 	},
							// 	fail: () => {
									
							// 	},
							// 	complete: () => {
									
							// 	}
							// })
						}else{
							
							uni.setStorageSync("user",res.data)
							uni.setStorageSync("authorization",res.data.data.token)
							uni.switchTab({
								url:'/pages/index/index'
							})
							console.log(res.data)
							uni.showToast({
								icon:"success" ,
								title:"登入成功",
								duration: 2000
							});
						}

					}
				})
			}
		}
	}
</script>

<style>
.tabnumber{
/* border: 1px #2979FF solid */
width: 80%;
height: 80rpx;
border-radius: 40px;
background-color: white;
border: 1px #2979FF solid;
font: 1em sans-serif;
text-align: left;
padding-left: 30rpx;
margin-left: 60rpx;
margin-top: 30rpx;
box-shadow: 10rpx 5rpx blue  ;
}
.pasnum{
width: 80%;
height: 80rpx;
border-radius: 40px;
background-color: white;
border: 1px #2979FF solid;
font: 1em sans-serif;
text-align: left;
padding-left: 30rpx;
margin-left: 60rpx;
margin-top: 20rpx;
/* margin-bottom: 25rpx; */
box-shadow: 5rpx 5rpx blue  ;
}
.back{
    height: 100vh;
    background: linear-gradient(aliceblue, azure);	
	
}
.login{
	/* background-color: #f1ffff ; */
	background-color: aliceblue;
	width: 100%;
	height: 500rpx;
	top: 200rpx;
	display: inline-block;
	margin-top: 200rpx;
	text-align: center; 
}

.right{
	margin-top: 50rpx;
	width: 80%;
	border-radius: 25px;
	box-shadow: 12rpx -10rpx turquoise;
	margin-bottom: 20rpx;
}
</style>
