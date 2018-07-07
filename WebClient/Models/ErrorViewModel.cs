using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace WebImage2Text.Models
{
    public class ErrorViewModel
    {
        private int _ErrorCode;
        public string ErrorDetail { get; set; }

        public int ErrorCode
        {
            get
            {
                switch (_ErrorCode)
                {
                    case 0://没上传图片
                        ErrorDetail = "图片上传不成功";
                        break;
                    case 1:
                        ErrorDetail = "转换机的画笔断水了 >_< (image2text本体异常中止)";
                        break;
                    case 2:
                        ErrorDetail = "没有图怎么画得出来了辣>_< (参数传递有误)";
                        break;
                    default:
                        ErrorDetail = "真的我也不知道是怎么回事...(Unexpected Internal Error)";
                        break;
                };
                return _ErrorCode;
            }
            set
            {
                _ErrorCode = value;
            }
        }

    }
}
