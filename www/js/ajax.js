function get_lan_advance()
{
	
	// var lan_ip = "0.0.0.0";						
	// var dhcpd_en = 1;
	// var start_ip= "0.0.0.0";
	// var end_ip = "0.0.0.0";
	// var leasetime = 0;
	
	var cpuUsed = 0;
	var ramUsed = 0;
	// var req_mode = "get";
	var jsonObjGet = {

				// "lan_ip":lan_ip,
				// "dhcpd_en":dhcpd_en,
				// "start_ip":start_ip,
				// "end_ip":end_ip,
				// "leasetime":leasetime
				// "req_mode":req_mode,
				"cpuUsed":cpuUsed,
				"ramUsed":ramUsed
	};
	


	var jsonStr = JSON.stringify(jsonObjGet);
		//toJSONString
		//processData:false,
		
	$.ajax({
		type:"POST",
		url:"/json.cgi",
		data:jsonStr,
		contentType: "application/json",
		dataType:"json",
		success:function(jsonRet){
			console.log(jsonRet);
			var jsonStr = JSON.stringify(jsonRet);
			$("#jsonRet").html(jsonStr);
			// var jsonRet = {

			// 	"lan_ip":"192.168.88.254",
			// 	"dhcpd_en":"1",
			// 	"start_ip":"192.168.88.100",
			// 	"end_ip":"192.168.88.200",
			// 	"leasetime":"480"
			// };

			//traverse_json_obj(jsonRet);
			// $("#lan_ip").val(jsonRet.lan_ip);
			// display_switch("dhcpd_en", jsonRet.dhcpd_en);
			
			// var stip = new Array;
			// stip = jsonRet.lan_ip.split(".");
			// var sturl= stip[0] + "." + stip[1] + "." + stip[2];
			// $("#startip1").val(sturl);
			// $("#endip1").val(sturl);
			// $("#startip4").val(jsonRet.start_ip.split(".")[3]);
			// $("#endip4").val(jsonRet.end_ip.split(".")[3]);
			// $("#leasetime").val(jsonRet.leasetime/60);
			// display_dhcpd_relate(jsonRet.dhcpd_en);
		},
		error:function(){
			
		}
		
	});

}

function set_lan_advance()
{
	
	var lan_ip = $("#lan_ip").val();
	var stip = new Array;
	stip = lan_ip.split(".");										
	var dhcpd_en = $("#dhcpd_en").attr("class").includes("switchoff") ? 0 : 2;
	var start_ip= stip[0] + "." + stip[1] + "." + stip[2] + "." + $("#startip4").val();
	var end_ip = stip[0] + "." + stip[1] + "." + stip[2] + "." + $("#endip4").val();
	var leasetime = $("#leasetime").val() * 60;
	
	var jsonObjGet = {

				"lan_ip":lan_ip,
				"dhcpd_en":dhcpd_en,
				"start_ip":start_ip,
				"end_ip":end_ip,
				"leasetime":leasetime,
	};
	
	var jsonStr = JSON.stringify(jsonObjGet);
		//toJSONString
		//processData:false,
		
	$.ajax({
		type:"POST",
		url:"/json.cgi",
		data:jsonStr,
		dataType:"json",
		success:function(jsonRet){
			//traverse_json_obj(jsonRet);
			if(jsonRet.result == "success")
			{
				console.log("OK !");
				window.location.reload(); 
			}else
			{
				console.log("Faild" + jsonRet.result);
			}
		},
		error:function(){
			
		}
		
	});

}



function json_obj_wlan_format(wl_ifname, jsonObj){
	var jsonStr = "{"
	var i = 0;
	for(var p in jsonObj){
		if(i++ != 0 ){
			jsonStr += ","
		}
		jsonStr += ('"' + wl_ifname +'_' + p + '"'+  ":" +'"'+ jsonObj[p]+'"');
	}
	jsonStr += "}"

	return jsonStr;
}

function get_wl_base_conf(wlan_idx)
{
	
	var enable = 0;
	var ssid = 0;
	var hidden = 0;
	//var hidden = $('#hidden').is(':checked') ? 1 :0;	
	var channel = 0;
	var bandwidth = 0;
	var security = 0;
	//var ciphersuite = $('input[name="ciphersuite"]').filter(':checked').val();
	var ciphersuite = 0;
	
	var passphrase = 0;
	var RFPower = 0;

	var jsonObjGet = { 
				"enable":enable,
				"ssid":ssid,
				"hidden":hidden,
				"channel":channel,
				"bandwidth":bandwidth,
				"security":security,
				"ciphersuite":ciphersuite,
				"passphrase":passphrase,
				"RFPower":RFPower
	};
		
	var jsonStr =json_obj_wlan_format("wlan"+wlan_idx, jsonObjGet);
		
	$.ajax({
		type:"POST",
		url:"/getinfo",
		data:jsonStr,
		dataType:"json",
		success:function(jsonRet){
			//traverse_json_obj(jsonRet);
			
			display_switch("enable", jsonRet.enable);
			$("#ssid").val(jsonRet.ssid);
			$("#hidden").attr("checked", (jsonRet.hidden == "1"? true:false));
			$("#channel").val(jsonRet.channel);
			$("#channelbound").val(jsonRet.bandwidth);
			$("#security").val(jsonRet.security);
			$("#ciphersuite" + jsonRet.ciphersuite).attr('checked', 'checked');
			$("#passphrase").val(jsonRet.passphrase);
			$("#RFPower").val(jsonRet.RFPower);

			LoadSetting();
			

		},
		error:function(){
			
		}
		
	});

}

function set_wl_base_conf(wlan_idx)
{
	
	var enable = $("#enable").attr("class").includes("switchoff") ? 0 : 1
	var ssid = $("#ssid").val();
	var hidden = $('#hidden').is(':checked') ? 1 :0;	
	var channel = $("#channel").val();
	var bandwidth = $("#channelbound").val();
	var security = $("#security").val();
	var ciphersuite = $('input[name="ciphersuite"]').filter(':checked').val();
	var passphrase = $("#passphrase").val();
	var RFPower = $("#RFPower").val();

	var jsonObjGet = { 
				"enable":enable,
				"ssid":ssid,
				"hidden":hidden,
				"channel":channel,
				"bandwidth":bandwidth,
				"security":security,
				"ciphersuite":ciphersuite,
				"passphrase":passphrase,
				"RFPower":RFPower
	};
	
	var jsonStr =json_obj_wlan_format("wlan"+wlan_idx, jsonObjGet);

		
	$.ajax({
		type:"POST",
		url:"/setinfo",
		data:jsonStr,
		dataType:"json",
		success:function(jsonRet){
			//traverse_json_obj(jsonRet);
			if(jsonRet.result == "success")
			{
				console.log("OK !");
				window.location.reload(); 
			}else
			{
				console.log("Faild" + jsonRet.result);
			}
			
		},
		error:function(){
			
		}
		
	});

	window.parent.showConfProcess();
}