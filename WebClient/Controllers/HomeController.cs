using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using WebImage2Text.Models;
using Microsoft.Extensions.Options;
using System.Text;

namespace WebImage2Text.Controllers
{
    public class HomeController : Controller
    {

        private AppSettings AppSettings { get; set; }
        public IActionResult Error()
        {
            int Code = -3;
            if (int.TryParse(Request.Query["id"], out Code))
            {
                return View(new ErrorViewModel { ErrorCode = Code });
            }
            return View(new ErrorViewModel { ErrorCode = -1 });
        }

        public HomeController(IOptions<AppSettings> settings)
        {
            AppSettings = settings.Value;
            Console.WriteLine("Image2Text WebServer is running! >_<");
        }
        public IActionResult Image2Text()
        {
            return View();
        }
        [HttpPost("UploadImage")]
        public ContentResult UploadImage([FromServices]IHostingEnvironment env, List<IFormFile> SourceImage, ImageViewModel Model)
        {
            // full path to file in temp location
            var NowTimeStamp = DateTime.Now.ToString("MMddHHmmss");
            var FilePath = env.WebRootPath + "/upload/" + NowTimeStamp + "." + SourceImage.First().FileName.Split('.').Last();
            if (SourceImage.Count != 0)
            {
                HttpContext.Session.SetString("FilePath", FilePath);
                HttpContext.Session.SetString("ScaleX", Model.ScaleX.ToString());
                HttpContext.Session.SetString("ScaleY", Model.ScaleY.ToString());
                HttpContext.Session.SetString("TimeStamp",NowTimeStamp);
                SaveImage(FilePath, Model.SourceImage);
            }
            return Content("success");
        }
        public IActionResult DownloadText([FromServices]IHostingEnvironment env)
        {
            var SessionResult = GetSessionKey(HttpContext.Session);
            if (SessionResult.Count == 0)
            {
                return View("Error", new ErrorViewModel { ErrorCode = 2 });
            }
            try
            {
                string Param = "--source={0} --scalex={1} --scaley={2} --type={3} --output={4}";
                var FilePath = env.WebRootPath + "/generatetxt/" + SessionResult["TimeStamp"] + ".txt";
                Param = String.Format(Param, SessionResult["UploadFileName"], SessionResult["ScaleX"], SessionResult["ScaleY"], 0, FilePath);
                if(ImageProcesser.Instance.GenerateTxt(AppSettings.ExecuteFileName, Param)==0)
                {
                    if (System.IO.File.Exists(SessionResult["UploadFileName"])) System.IO.File.Delete(SessionResult["UploadFileName"]);
                    FileStream TxtStream = new FileStream(FilePath, FileMode.Open);
                    return File(TxtStream, "text/plain",SessionResult["TimeStamp"] + ".txt");
                }
            }
            catch 
            {
                return View("Error", new ErrorViewModel { ErrorCode = -1 });
            }
            return View("Error", new ErrorViewModel { ErrorCode = -1 });
        }
        public string ShowColorHtml()
        {
            return "Show Color Html";
        }
        public Dictionary<string, string> GetSessionKey(ISession HttpSession)
        {
            string UploadFileName = HttpContext.Session.GetString("FilePath");
            string ScaleX = HttpContext.Session.GetString("ScaleX");
            string ScaleY = HttpContext.Session.GetString("ScaleY");
            string TimeStamp= HttpContext.Session.GetString("TimeStamp");
            Dictionary<string,string> SessionKey;
            if (!(string.IsNullOrEmpty(UploadFileName) && string.IsNullOrEmpty(ScaleX) && string.IsNullOrEmpty(ScaleY) && string.IsNullOrEmpty(TimeStamp)))
            {
                SessionKey = new Dictionary<string, string>{{ "UploadFileName", UploadFileName },{ "ScaleX", ScaleX },{ "ScaleY", ScaleY } , { "TimeStamp", TimeStamp } };
                return SessionKey;
            }
            return new Dictionary<string, string>();
        }
        public IActionResult ShowCharGraphHtml()
        {
            var SessionResult = GetSessionKey(HttpContext.Session);
            if(SessionResult.Count==0)
            {
                return View("Error", new ErrorViewModel { ErrorCode = 2 });
            }
            HttpContext.Session.Clear();
            string Param = "--source={0} --scalex={1} --scaley={2} --type={3}";
            Param = String.Format(Param, SessionResult["UploadFileName"], SessionResult["ScaleX"], SessionResult["ScaleY"], 1);
            int ExitCode;
            ViewData["Result"] = ImageProcesser.Instance.GenerateOutputString(AppSettings.ExecuteFileName, Param, out ExitCode);
            if (ExitCode != 0)
            {
                if (System.IO.File.Exists(SessionResult["UploadFileName"])) System.IO.File.Delete(SessionResult["UploadFileName"]);
                return View("Error", new ErrorViewModel { ErrorCode = 1 });
            }
            return View("CharGraphHtml");
        }
        public bool SaveImage(string FilePath, List<IFormFile> SourceImage)
        {
            try
            {
                foreach (var formFile in SourceImage)
                {
                    if (formFile.Length > 0)
                    {
                        using (var stream = new FileStream(FilePath, FileMode.Create))
                        {
                            formFile.CopyTo(stream);
                        }
                    }
                }
                return true;
            }
            catch
            {
                return false;
            }
        }
        
    }
}