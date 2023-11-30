<template>
	<view>
		<uni-card padding="0" spacing="0" style="background-color: gainsboro; ">
					<template v-slot="cover">
						<view style="padding: 0rpx; margin-top: 0; position: relative;">
			
							<image 
							mode="aspectFill" 
							style="
							display: block;
							border-radius: 10rpx;
							width: 100%;
							margin-top: 0;
							"
							:src="coverSrc"
							>
							</image>
							<view style="position: absolute; right: 10rpx; font-size: 13px; top:10rpx;color: darkblue; background-color:azure; border-radius: 6px;
							padding-left: 12rpx;
							padding-right:12rpx ;
							">
								<image src="../../../static/images/time.png" style="width: 40rpx; height: 40rpx; top: 8rpx; right: 3rpx;" mode=""></image>
								<text>发售中</text>
								</view>
						</view>
						
						
					</template>
				</uni-card>
				<view class="
						" style="background-color: lightblue">
						<view class="" style="margin-bottom: -8rpx;display: flex; justify-content: space-between; ">
							<text>name</text>
							
							<view class="" style="
							display: inline-block;
							 font: 0.8em sans-serif;
							
							 ">限量
							 <text>1份</text>
							 </view>
						</view>
						<view class="" style="height: 25px;">
							<!-- <view style="display:inline-block; margin-top:-8rpx;border-radius:3px; background-color:coral;color: darkturquoise; font: 0.9em sans-serif; margin-left:3rpx;">
								 NFT</view> -->
								 <uni-tag text="NFR" type="warning" size="mini"></uni-tag>
								</view>
						</view>
						<view class=""style="flex-flow:row;justify-content: space-between;display: flex;">
							<view class="" style="">
								<view class="" style="height: 13px; font: 0.7em sans-serif " >创作者</view> 
								<view style="color: rebeccapurple; font: 0.8em sans-serif;">WeiMo</view>
							</view>
							
							<view style="color: black; font-size: 40rpx; ">123</view>
							</view>
				<view class="" style="font-size: 12px;">
					合约地址：
				</view>
				<view class="" style="height: 500px;">
					作品描述
				</view>
				
				<view class="" style="padding: 12rpx;padding-bottom: 36rpx;">
					<view class="" style="color: #353535;
						text-align: center;
						line-height: 3;">
						关于数字藏品
					</view>
					<view class="" style="color:#909399; font-size: small">
						数字藏品为虚拟数字商品，该藏品为实物凭证，持有可对实物储物柜进行支配，拥有开或关门的执行权，该产品为特殊藏品，仅供开发者一人使用，开发者本人拥有对该藏品相关事务的最高解释权与执行权。
						
						仅限实名认证为年满14周岁的中国大陆用户购买。该数字藏品的版权由原创者拥有，除另外取得版权拥有者书面同意外，用户不得将数字藏品用于任何商业用途。本商品一经售出，不支持退换。本商品源文件不支持本地下载。请勿对数字藏品进行炒作、场外交易、欺诈、或以任何其他非法方式进行使用。
					</view>
				</view>
				
				<view class="dom">
					
					<button @click="remint()" :disabled="openQ" type="primary" size="mini" style="background-color: #66ccff;width: 40%;height: 70%;top: 20rpx;border-radius: 50px;position:absolute;right: 10rpx;" >Mint</button>
					<uni-popup ref="popup" background-color="#fff">
						<text>订单信息</text>
						<view class="gw">
							<view>
									<text>NAME</text>
									<text>$</text>
								</view>
							<view class="">
								<uni-number-box :min="1"></uni-number-box>
							</view>
							<view class="">
								<!-- <uni-data-checkbox></uni-data-checkbox> -->
								
							</view>
							<view class="gbut">
								
								<button type="primary">立刻购买</button>
							</view>
							
						</view>
						
					</uni-popup>
				</view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				coverSrc:'/static/images/boxoff.jpg',
				openQ:false,
				item:{}
			}
		},
		mounted() {
			this.isopen();
		},
		methods:{
			remint(){
				uni.hideLoading();
				this.showLoading();
			        this.request({
			        				url:'/api/rsmint',
			        				method: 'GET'
								}).then(res => {
			        				uni.hideLoading();
									uni.showToast({
										title: res.data,
										duration: 5000
									});
									uni.switchTab({
										url:"/pages/index/index"
									})
									}
									// fail:()=>{}
									)
			      },
			isopen(){
				this.request({
								url:'/api/isopen',
								method: 'GET',
							}).then(res => {
								this.openQ=!res
								if(res){
									// this.openQ = JSON.parse(!res)
									// console.log("------res------",this.openQ)
									this.coverSrc='/static/images/boxon.jpg'
								}
								console.log(this.openQ)
								
							})
				// let token = uni.getStorageSync('authorization')
				// 	uni.request({
				// 		url:"http://localhost:8080/api/isopen",
				// 		method:"GET",
				// 		header: {
				// // 根据实际接口设计 key 取 token 或者 authorization
				// token: token},
				// success: (res) => {
				// 	console.log(res)
				// }
				// 	})
		
			},
			showLoading: function () {
			
			       console.log(this.titleSelect)
			       if (this.titleSelect == "null") {
			         uni.showLoading({
			           title: "",
			           mask: this.maskSelect
			         });
			       } else {
			         uni.showLoading({
			           title: this.titleSelect,
			           mask: this.maskSelect
			         });
			       }
			       // setTimeout(function () {
			       //   uni.hideLoading();
			       // }, 3000);
			     }
			
		},
		
	onLoad: function (option) { //option为object类型，会序列化上个页面传递的参数
			//   this.item = JSON.parse(decodeURIComponent(option.item));
			}

		}
</script>

<style>
.dom{
	width: 100%;
	height: 110rpx;
	position: fixed;
	background-color: dodgerblue;
	bottom: 0;
	border-top-left-radius: 12px;
	border-top-right-radius: 12px;
}
.gw{
	height: 600rpx;
}
.gbut{
	position: absolute;
	bottom: 50rpx;
	width: 90%;
	/* height: 100rpx; */
	left: 40rpx;
}
</style>
