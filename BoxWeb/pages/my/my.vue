<template>
    <!--myhtmlStart-->

    <view id="defaultId1">
		<view style="background-color: aliceblue;">
        <view id="id5TmLWO" class=" ugonX4C">
            <view id="idr3PjZf" class=" u8Wi7iQ">
                <view id="id1ZMlRV" class=" u6zdVqx">
                    <!-- <image id="idIFUUE3" class=" uTXgfWT" src="../../static/images/Tjfx.png" >
                    </image> -->
					<uni-icons type="contact" :size="65"></uni-icons>
                    <view id="gecce8" class="  u7a687" @click="tolog()">
                        <view id="g2ce23">
                            <text id="g71301" class="  ueb182">{{user.username}}
                            </text>
                        </view>
                        <view id="gb9545" class="  u466ed">
                            <view id="g61668" class="  u04dd9">未实名
                            </view>
                        </view>
                        <text id="g0309a" class="  u24ebb">邀请码: 6xfaw2
                        </text>
                    </view>
                </view>
            </view>
           <u-grid id="c556d3" class=" urhctvv" ids="c556d3" :border="true">
                <u-grid-item id="c9a417" v-for="(listItem,listIndex) in list" class=" ulJ9XDC" :key="listIndex" customStyle="padding-top: 10px; padding-bottom: 2rpx">
                   <image :src="listItem.src" style="width: 75rpx;height: 75rpx;filter: drop-shadow(4rpx 1px yellow);"></image>
					<text id="c34dee" class="grid-text uaHs4l2">
                        {{listItem.title}}
                    </text>
                </u-grid-item>
            </u-grid>
			
			<view class="" style="height: 140rpx;padding: 6rpx; margin: 30rpx 40rpx 20rpx 25rpx;background-color: rgba(110, 192, 210, 1.0);border-radius: 10px;box-shadow: 1px 1px 1px steelblue;">
				<text style="font: 0.9em sans-serif;color: wheat;padding-left: 20rpx;">钱包</text>
				<view style="margin-left: 16rpx;">
				<image src="/static/images/qb.png"
				style=" height: 80rpx;width: 75rpx;margin-right:10rpx ; vertical-align: middle;"
				></image>
				<text style="color: khaki;">CFX:</text>
				<text style="color: whitesmoke;margin-left: 10rpx;">1.42</text>
				</view>
				
			</view>
			<view class="" style="height: 80rpx;padding: 15rpx;margin: 0 40rpx 20rpx 25rpx;background-color:#8cb4c9;border-radius: 10px;color: white;padding-top: 8rpx;padding-bottom: 20rpx;
				box-shadow: 1px 1px 1px #ccc;
			">
				<image src="../../static/images/qkl.png" style="width:60rpx;height: 60rpx;display: inline-block;top: 14rpx;padding-right: 12rpx;"></image>
				<text>区块链地址: 0x5B38Da6a701c...</text>
				
				
			</view>
        </view>
		<view class="" style="background-color: white;margin-top: 240rpx;border-radius: 15rpx;width: 98%;margin-left: 8rpx;">
			<view class="handeable"><text>我的藏品</text> </view> 
			
			<scroll-view class="scroll-view_H" scroll-x="true" scroll-left="120">
			<view :class="[curr === index?'nftcons' : 'nle']" v-for="(item, index) in nftowenlist" :key="index">
				<view class="ble" @click="_onclick(index)" >{{item.name}}</view>
			</view>
			</scroll-view>
			
			<uni-grid :column="2" :square="false" :show-border="false" >
				<uni-grid-item  v-for="(item, index) in temp" :key="index">
					<view @click="tonftxs()" class="" style="margin: 3rpx; height: 400rpx;background-color: #eee; ">
					<image :src="item.image" style="width: 95%;margin-top: 5rpx; margin-left: 10rpx; height: 80%; border-radius: 10px;"></image>
					<text style=" margin-left: 6px;font: 0.8em sans-serif;">{{item.name}}</text> 
					
					</view>
					<view class=""></view>
				</uni-grid-item>
				
			</uni-grid>
			
		
			
		</view>
		
		
		<view class="" style="margin-top: 120rpx;">
			<view style="text-align: center; ">
			<image src="../../static/images/confluxi.png" style="width: 160rpx; height: 38rpx;"></image>
					<text style="font-size: 20rpx;">提供技术支持</text>
					</view>
				</view>
		<view>
			<view class="" style="font-size: 0.7em;text-align: center; "><text>凡霄工作室</text></view> 
			<view class="" style="font-size: 0.7em;text-align: center;"><text>增值电信经营许可证:无</text></view>
			<view class="" style="font-size: 0.7em;text-align: center;"><text>网络文化经营许可证:无</text></view>
			<view class="" style="font-size: 0.7em;text-align: center;"><text>备案号 未备案</text></view>
			<view class="" style="font-size: 0.7em;text-align: center;"><text>@2023 FuJian Weimo.All Rights Reserved</text></view>
		</view>
    </view>
    <!--myhtmlEnd-->
</view>
</template>

<script>
    export default {
        data() {
            return {
                // insertData
                // myDataStart
				user:{},
				curr:0,
				address:'0x8f3f840ebdd28cdcfaca3b47ffaeb1ba26b45208',
				nftowenlist:[],
				nftlist:[],
				temp:[],
                list: [{
                        "name": "photo",
                        "title": "订单",
						"src":"/static/images/dd.png"
                    },
                    {
                        "name": "lock",
                        "title": "转赠",
						"src":"/static/images/zz.png"
                    },
                    {
                        "name": "star",
                        "title": "类型",
						"src":"/static/images/lx.png"
                    },
                    {
                        "name": "hourglass",
                        "title": "空投",
						"src":"/static/images/lw.png"
                    }
                ]
                // myDataEnd

            }
        },
		mounted() {
			
			this.user = uni.getStorageSync("user").data
			this.address = this.user.web3user
			// this.getnft_balances()
			uni.request({
				url:"https://evmapi.confluxscan.net/nft/owners?contract=0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5&tokenId=0&cursor=0&limit=10",
				method:"GET",
				success: (res) => {
					if(res.data.result.list[0].address === this.address){
						this.nftowenlist={"0":{"owner":"0x3e26507ac73a333146e3e40f7887093a8d5fa0b0","contract":"0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5","balance":"1","name":"MyIotbox","symbol":"MIb","type":"ERC721","webSite":null,"iconUrl":null}}
							this.temp.push({"image":"/static/images/boxoff.jpg","name":"#01"});
						
					}
				}
			})
			// if(this.nftowenlist.length>3){
			// 	this.nftowenlist={}
			// 	this.nftowenlist={"0":{"owner":"0x3e26507ac73a333146e3e40f7887093a8d5fa0b0","contract":"0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5","balance":"1","name":"MyIotbox","symbol":"MIb","type":"ERC721","webSite":null,"iconUrl":null}}
			// 	this.temp = [];
			// 	this.temp.push({"image":"/static/images/boxoff.jpg","name":"#01"});
			// }
			// this.nftowenlist={"0":{"owner":"0x3e26507ac73a333146e3e40f7887093a8d5fa0b0","contract":"0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5","balance":"1","name":"MyIotbox","symbol":"MIb","type":"ERC721","webSite":null,"iconUrl":null}}
			// this.curr=1;
			// this.getnft(this.nftowenlist[0].contract)
			// uni.request({//https://evmapi.confluxscan.net/nft/preview?contract=0x3E26507aC73A333146E3E40f7887093a8d5fA0B0&tokenId=100067&withMetadata=false
			// 	url: 'https://evmapi.confluxscan.net/nft/preview',
			// 	method: 'GET',
			// 	data: {contract:"0x564fcdb3a585871f8c25ccf9cc73a6846ec833d5",tokenId:0,withMetadata:false},
			// 	success: res => {
			// 		// console.log(res.data.result)
			// 		// this.temp = res.data.result;
			// 		// this.temp =[...this.temp,...res.data.result] ;
			// this.temp.push({"image":"/static/images/boxoff.jpg","name":"#01"})
			// this.temp[0].image="/static/images/boxoff.jpg"
			// 		console.log(res.data.result)
				
			// 	},
			// 	fail: () => {},
			// 	complete: () => {}
			// });
			// this.getnft("0x564FCdB3a585871F8C25CcF9cc73a6846EC833D5");
			// console.log("----------res-------",this.user)
		},
        methods: {
            // insertMethod
            // myMethodStart

            // myMethodEnd
			getnft_balances(){
				uni.request({
					url: 'https://evmapi.confluxscan.net/nft/balances',
					method: 'GET',
					data: {owner:this.address,skip:0,limit:10},
					success: res => {
					// console.log(res.data.result.list);
					this.nftowenlist=res.data.result.list;
					this.getnft(this.nftowenlist[0].contract);
					},
					fail: () => {},
					complete: () => {}
				});
			},
			tolog(){
				uni.navigateTo({
					url:"/pages/my/login/login"
				})
			},
			getnft(con){
				uni.request({//https:evmapi.confluxscan.net/nft/tokens?owner=0x8f3f840ebdd28cdcfaca3b47ffaeb1ba26b45208&contract=0x6cf1c8de97bb607f3619f8a3148e1c9980224bc6&skip=0&limit=10&detail=false&withBrief=false&withMetadata=false
					url: 'https://evmapi.confluxscan.net/nft/tokens',
					method: 'GET',
					data: {owner:this.address,contract:con,skip:0,limit:10,detail:false,withBrief:false,withMetadata:false},
					success: res => {console.log(res);
									this.nftlist=res.data.result.list;
									for(let i =0; i< this.nftlist.length;i++){
										this.getnftpt(this.nftlist[i].contract,this.nftlist[i].tokenId);
										
									}
					},
					fail: () => {},
					complete: () => {}
				});
			},
			
			getnftpt(cadd,id){
				uni.request({//https://evmapi.confluxscan.net/nft/preview?contract=0x3E26507aC73A333146E3E40f7887093a8d5fA0B0&tokenId=100067&withMetadata=false
					url: 'https://evmapi.confluxscan.net/nft/preview',
					method: 'GET',
					data: {contract:cadd,tokenId:id,withMetadata:false},
					success: res => {
						// console.log(res.data.result)
						// this.temp = res.data.result;
						// this.temp =[...this.temp,...res.data.result] ;
						this.temp.push(res.data.result)
						console.log(res.data.result)
					},
					fail: () => {},
					complete: () => {}
				});
			},
			
			_onclick(index){
				console.log(index);
				this.temp=[];
				this.getnft(this.nftowenlist[index].contract);
					this.curr=index;
			},
			
			tonftxs(){
				uni.navigateTo({
					url:"/pages/have/have"
				})
			}
        }
    }
</script>

<style scoped>
    .mycssStart {}

    .ugonX4C {
        display: block;
        width: 100%;
        height: 400rpx;
        box-sizing: inherit;
		border-radius: 5px;
        background-color: rgba(0, 178, 255, 1);
    }

    .u8Wi7iQ {
        width: inherit;
        height: 125rpx;
        box-sizing: inherit;
        background: black;
        background-color: #000000;
    }

    .u6zdVqx {
        display: flex;
        justify-content: flex-start;
        align-items: flex-start;
        width: auto;
        height: inherit;
        flex-direction: row;
        flex-wrap: nowrap;
        background-color: rgba(0, 178, 255, 1);
    }

    .uTXgfWT {
        display: block;
        width: 120rpx;
        height: 120rpx;
        margin-top: 5rpx;
        margin-left: 10rpx;
        flex-direction: row;
        box-sizing: inherit;
        /* background-color: rgba(144, 238, 144, 1); */
		background-color: white;
        overflow-x: hidden;
        overflow-y: hidden;
        border-top-left-radius: 100rpx;
        border-bottom-left-radius: 100rpx;
        border-top-right-radius: 100rpx;
        border-bottom-right-radius: 100rpx;
        flex: none;
        border-color: rgba(255, 0, 0, 1);
        border-width: 1px;
        border-style: solid;
    }

    .u7a687 {
        display: flex;
        width: 100%;
        height: inherit;
        margin-top: 10rpx;
        margin-left: 10px;
        flex-direction: column;
        box-sizing: inherit;
    }

    .ueb182 {
        color: rgba(255, 120, 0, 1);
        margin-top: 4rpx;
        margin-left: 12rpx;
        word-break: break-all;
        text-overflow: ellipsis;
        overflow: hidden;
        -webkit-line-clamp: 1;
        -webkit-box-orient: vertical;
        margin-bottom: 4rpx;
    }

    .u466ed {
        display: flex;
        height: 30rpx;
        margin-left: 13rpx;
    }

    .u04dd9 {
        display: block;
        width: max-content;
        height: 36rpx;
        margin-top: 3rpx;
        font-weight: normal;
		color: white;
        font-size: 22rpx;
        box-sizing: border-box;
        background-color: rgba(157, 157, 157, 1);
        overflow-x: initial;
        overflow-y: initial;
        border-top-left-radius: 10rpx;
        border-bottom-left-radius: 10rpx;
        border-top-right-radius: 10rpx;
        border-bottom-right-radius: 10rpx;
        flex: none;
        box-shadow: 2px 1px 1px 0rpx #ccc;
        text-align: left;
        padding-left: 4px;
        padding-right: 3px;
        line-height: 15px;
        cursor: default;
    }

    .u24ebb {
        align-items: center;
        color: rgba(85, 0, 255, 1.0);
        margin-top: 12rpx;
        font-weight: lighter;
        font-size: 24rpx;
        margin-left: 16rpx;
        position: static;
    }

    .urhctvv {
        display: flex;
        justify-content: space-around;
        align-items: center;
        margin-top: 30rpx;
        flex-direction: row;
        border-color: rgba(255, 0, 0, 1);
        border-width: 2px;
        border-style: none;
        border-left-style: none;
        border-left-width: 4px;
        border-left-color: rgba(255, 0, 0, 1);
		
    }

    .ulJ9XDC {
        /* width: 20%; */
        height: inherit;
        box-sizing: inherit;
		
        /* border-right-width: 2px; */
        /* border-right-color: rgba(255, 0, 0, 1);
        border-right-style: solid; */
    }

    .uaHs4l2 {
        display: block;
        justify-content: center;
        align-items: flex-end;
        width: auto;
        height: inherit;
        flex-direction: row;
        box-sizing: inherit;
		padding-left: 7rpx;
		font-size: 14px;
        /* border-right-width: 3px; */
        
		/* text-shadow: 1px 1px #ccc; */ 
    }

    .ubPPGH3 {
        border-color: rgba(255, 0, 0, 1);
        border-width: 2px;
        border-style: solid;
    }

    .mycssEnd {}
	
	.handeable{
		color: burlywood;
		position: relative;
		top: -34rpx;
		left: 14rpx;
		font-size:18px;
	}
	
	.ble{
		/* background-color: #000000; */
		/* width: 20rpx;
		height: 100rpx; */
		margin: 10px;
		/* color: lightcyan; */
		/* display: inline-block; */
		/* flex: 1; */
		font-size: 12px;
		/* vertical-align: top; */
	}
	.nle{
		display: inline-flex;
		white-space: nowrap;
		overflow-x: auto;
		flex-direction: column;
		background-color: rgba(30, 61, 228, 0.04);;
		color: #000;
		margin: 6rpx;
		border-radius: 15px;
		height: inherit;
	}
	.nftcons{
		display: inline-flex;
		white-space: nowrap;
		overflow-x: auto;
		flex-direction: column;
		background-color: rgba(30, 61, 228, 0.8);
		color: lightcyan;
		margin: 6rpx;
		border-radius: 15px;
		height: inherit;
		/* flex-direction: row; */
	}
	
	.scroll-view_H{
		height: 80rpx;
		white-space: nowrap;
		vertical-align: top;
		margin-top: -30rpx;
		margin-bottom: 10rpx;
		
	}
</style>

// myMountedStart

// myMountedEnd