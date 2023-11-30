<template>
	<view class="content">
		<uni-nav-bar dark :fixed="true" type="line" style="margin-bottom: 3px;" background-color="#007AFF" title="首页"></uni-nav-bar>
	<!-- 	<uni-section title="自定义高度" subTitle="使用 height 修改组件高度" type="line"  style="margin-bottom: 0 padding: 0;display: block;">
							<uni-nav-bar height="40px" :fixed="true" background-color="#007AFF" dark=""
								title="首页"/>			
				</uni-section> -->
		<view class="wpaper" >
			<swiper :indicator-dots="true" :autoplay="true" :interval="3000" :duration="1000">
				<swiper-item><view class="swiper-item">了解我们</view></swiper-item>
				<swiper-item><view class="swiper-item B">点击进入</view></swiper-item>
			</swiper>
			<!-- //通知栏 -->
			<uni-notice-bar showIcon single="true" scrollable="true" showClose="true" text="欢迎来到我的NFT平台,该平台处于内测阶段,概不对一切负责."></uni-notice-bar>
			
			<uni-segmented-control :values="citm" styleType="text" @clickItem="onClickItem" style="<!-- float: left; -->"></uni-segmented-control>
			 <view class="content">
			            <view v-show="current === 0">
							<uni-section title="2022-10-11 11:20" type="line" padding="false">
			                <uni-card padding="0" spacing="0" style="background-color: gainsboro; margin-top: 0; " @click="to()">
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
			                						<image src="../../static/images/time.png" style="width: 40rpx; height: 40rpx; top: 8rpx; right: 3rpx;" mode=""></image>
			                						<text>发售中</text></view>
			                						<view style="border-radius: 10rpx; position: absolute; bottom: 10rpx; left:5rpx;color: coral;background-color: lemonchiffon; ">
			                						<view class="" style="display: block;
			                						 font: 0.8em sans-serif;
													 padding-left: 10rpx;
													 padding-right: 10rpx;
													 ">限量<text>1份</text></view>
			                						</view>
			                					
			                				</view>
			                				
			                				<view class="
			                				" style="background-color: gainsboro; margin-left: 8rpx;">
			                				<view class="" style="margin-bottom: -8rpx;font: 1.3em sans-serif; color: firebrick; margin-left: 8rpx;" >
			                					<text>MyBox</text>
			                				</view>
			                				<view class="" style="height: 16px;" >
												<!-- <view style="display:inline-block; margin-top:-8rpx;border-radius:3px; background-color:coral;color: darkturquoise; font: 0.9em sans-serif; margin-left:3rpx;">
													 NFT</view> -->
													 
													 <uni-tag text="实体" type="yama" size="mini"></uni-tag>
													 
													</view>
			                				<view class=""style="flex-flow:row;justify-content: space-between;display: flex;">
												<view style="color: white;">WeiMo</view>
												<view style="color: black; font-size: 40rpx; ">$ 0.0</view>
												</view>
			                				
			                				</view>
			                			</template>
			                		</uni-card></uni-section>
			                	<view class="" v-for="(item, index) in data" :key="index" @click="devicechannel(item)">
									<uni-card padding="0" spacing="0" style="background-color: gainsboro; margin-top: 0; ">
												<template v-slot="cover" >
													<view style="padding: 0rpx; margin-top: 0; position: relative;">
										
														<image 
														mode="aspectFill" 
														style="
														display: block;
														border-radius: 10rpx;
														width: 100%;
														margin-top: 0;
														"
														:src="'https://h5.mto520.com/'+item.cover"
														>
														</image>
														<view style="position: absolute; right: 10rpx; font-size: 13px; top:10rpx;color: darkblue; background-color:azure; border-radius: 6px;
														padding-left: 12rpx;
														padding-right:12rpx ;
														">
															<image src="../../static/images/time.png" style="width: 40rpx; height: 40rpx; top: 8rpx; right: 3rpx;" mode=""></image>
															<text>发售中</text></view>
															<view style="border-radius: 10rpx; position: absolute; bottom: 10rpx; left:5rpx;color: coral;background-color: lemonchiffon; ">
															<view class="" style="display: block;
															 font: 0.8em sans-serif;
															 padding-left: 10rpx;
															 padding-right: 10rpx;
															 ">限量<text>1000份</text></view>
															</view>
														
													</view>
													
													<view class="
													" style="background-color: gainsboro">
													<view class="" style="margin-bottom: -8rpx;">
														<text>{{item.name}}</text>
													</view>
													<view class="" style="height: 16px;">
															 <uni-tag text="NFT" type="default" size="mini"></uni-tag>
															</view>
													<view class=""style="flex-flow:row;justify-content: space-between;display: flex;">
														<view style="color: white;">WeiMo</view>
														<view style="color: black; font-size: 40rpx; ">{{item.price}}</view>
														</view>
													
													</view>
												</template>
											</uni-card>
			                	</view>
			                </view>
							<view v-show="current === 1">
			                暂无活动
			            </view>
						<view class="" style="margin-top: 120rpx;">
							<view style="text-align: center; ">
							<image src="../../static/images/confluxi.png" mode="aspectFill " style="width: 160rpx; height: 38rpx;"></image>
									<text style="font-size: 20rpx;">提供技术支持</text>
									</view>
								</view>
			            </view>
						
						
							
						
			        </view>
					
			
			<!-- //卡片 -->
			
	</view>
</template>

<script>
export default {
	data() {
		return {
			citm:['发行', '活动'],
			// coverSrc:"/static/images/yy.jpeg",
			coverSrc:"/static/images/boxoff.jpg",
			current:0,
			data: {}
		};
	},
	mounted() {
		// this.getData();
		
	},
	onPullDownRefresh() {
		uni.stopPullDownRefresh();
	},
	onPageScroll(e) {
		this.scrollData = e;
	},
	methods:{
	 onClickItem(e) {
	      if (this.current != e.currentIndex) {
	        this.current = e.currentIndex;
	      }
	    },
	 devicechannel(item){
		 console.log(item)
	    uni.navigateTo({
	 	url:'/pages/shop/shop?item='+ encodeURIComponent(JSON.stringify(item))
	 })
	},
		to(){
		uni.navigateTo({
			url:"/pages/index/shop/shop"
		})	
		},

		    // 注意url有长度限制，过长会导致参数传递失败，可用encodeURIComponent方式解决。
		// <navigator :url="'/pages/info/index?item='+ encodeURIComponent(JSON.stringify(item))"></navigator>    
		 
		   
		getData() {
			uni.request({
				url: 'https://h5.mto520.com/api/sell/markets',//https://m.douyu.com/api/room/list
				method: 'GET',
				data: { type: 'LOL', page: 1 },
				success: res => {
					console.log(res);
					this.data = res.data.data;
				},
				fail: () => {},
				complete: () => {}
			});
		}
		
	}
	// <navigator :url="'/pages/shop/shop?item='+ encodeURIComponent(JSON.stringify(item))">
	// </navigator>
};
</script>
<style>
.wpaper {
	width: 100%;
	height: 300rpx;
}
.swiper-item {
	width: 100%;
	display: block;
	height: 100%;
	line-height: 300rpx;
	text-align: center;
	background-color: aqua;
}
.B {
	background-color: aquamarine;
}
.content{
	padding-bottom: var(--window-bottom);
}

</style>
