var _zcms_recommend_d,_zcms_recommend_s,_zcms_recommend_l,_zcms_recommend_m,_zcms_recommend_t;
var _zcms_recommend_st=new Date().getTime();
var _fingerID = 0
var _zcms_recommendstat = function(param){
	var p = {};
	if(param){
		var arr = param.split("&");
		for(var i=0;i<arr.length;i++){
			if(arr[i]){
				var arr2 = arr[i].split("=");
				if(arr2[0]){
					p[arr2[0]] = arr2[1];
				}
			}
		}
	}
	_zcms_recommend_d = p["Dest"];
	_zcms_recommend_s = p["SiteID"];
	_zcms_recommend_l = p["ContentID"];
	_zcms_recommend_t = p["RecommendType"];
	try{
    _fingerID =new Fingerprint().get();
  }catch (e) {
    console.warn("No fingerprints were obtained!")
  }

	var memberID=_zcms_recommendstat.cookieGet("_ZMemberID");
	if(memberID){
		_zcms_recommend_m = memberID;
	}
};

_zcms_recommendstat.mq = function(map){
	var sb = [];
	for(var prop in map){
		if(map[prop]){
			sb.push(prop+"="+map[prop]);
		}
	}
	return sb.join("&");
}

_zcms_recommendstat.trim = function(str){
	return str.replace(/(^\s*)|(\s*$)/g,"");
}

_zcms_recommendstat.cookieGet=function(name){
	var cs = document.cookie.split("; ");
	for (i = 0; i < cs.length; i++) {
		var arr = cs[i].split("=");
		var n = _zcms_recommendstat.trim(arr[0]);
		var v = arr[1] ? _zcms_recommendstat.trim(arr[1]) : "";
		if (n === name) {
			return decodeURIComponent(v);
		}
	}
	return null;
}

function _zcms_recommend_stat(){
	var sticktime = new Date().getTime()-_zcms_recommend_st;
	var p = {};
	p["SiteID"] = _zcms_recommend_s;
	p["ContentID"] = _zcms_recommend_l;
	p["StickTime"] = sticktime;
	p["MemberID"] = _zcms_recommend_m;
	p["RecommendType"] = _zcms_recommend_t;
  p["fingerID"] = _fingerID;
	var dest = _zcms_recommend_d+"?"+_zcms_recommendstat.mq(p);
	var s = document.createElement("script");
	s.src = dest;
	(document.getElementsByTagName("head")[0]||document.getElementsByTagName("body")[0]).appendChild(s);
}

if(window.attachEvent){
	window.attachEvent("onbeforeunload",_zcms_recommend_stat);
}else if(window.addEventListener){
	window.addEventListener('beforeunload',_zcms_recommend_stat,false);
}
