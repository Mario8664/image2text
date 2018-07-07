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
            int Code=-3;
            if(int.TryParse(Request.Query["id"], out Code))
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
        public ContentResult UploadImage([FromServices]IHostingEnvironment env, List<IFormFile> SourceImage,ImageViewModel Model)
        {
            // full path to file in temp location
            var FilePath = env.WebRootPath + "/upload/" + DateTime.Now.ToString("MMddHHmmss") + "." + SourceImage.First().FileName.Split('.').Last();
            if(SourceImage.Count!=0)
            {
                SaveImage(FilePath, Model.SourceImage);
                HttpContext.Session.SetString("FilePath", FilePath);
                HttpContext.Session.SetString("ScaleX", Model.ScaleX.ToString());
                HttpContext.Session.SetString("ScaleY", Model.ScaleY.ToString());
                int ProcessType;
                if (int.TryParse(Request.Form["ProcessType"], out ProcessType))
                {
                    switch (ProcessType)
                    {
                        case 0:
                            return Content("Home/ShowCharGraphHtml");
                        default:
                            break;
                    }
                }
            }
            return Content("Home/Error?id=0");
        }
        public string DownloadText()
        {
            return "Download txt file";
        }
        public string ShowColorHtml()
        {
            return "Show Color Html";
        }
        public IActionResult ShowCharGraphHtml()
        {
            byte[] UploadFileName, ScaleX, ScaleY;
            var Session = HttpContext.Session;
            if (Session.TryGetValue("FilePath",out UploadFileName)&& Session.TryGetValue("ScaleX",out ScaleX)&&Session.TryGetValue("ScaleY",out ScaleY))
            {
                HttpContext.Session.Clear();
                string Param = "--source={0} --scalex={1} --scaley={2} --type={3}";
                Param = String.Format(Param, Encoding.Default.GetString(UploadFileName), Encoding.Default.GetString(ScaleX), Encoding.Default.GetString(ScaleY), 1);
                int ExitCode;
                ViewData["Result"] = exec(AppSettings.ExecuteFileName, Param,out ExitCode);
                if(ExitCode!=0)
                {
                    return View("Error",new ErrorViewModel { ErrorCode = 1 });
                }
                
                return View("CharGraphHtml");
            }
            if (System.IO.File.Exists(Encoding.Default.GetString(UploadFileName))) System.IO.File.Delete(Encoding.Default.GetString(UploadFileName));
            return View("Error", new ErrorViewModel { ErrorCode = 2 });
        }
        public bool SaveImage(string FilePath,List<IFormFile> SourceImage)
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
        private string exec(string exePath, string parameters,out int ExitCode)
        {
            System.Diagnostics.Process pProcess = new System.Diagnostics.Process();
            pProcess.StartInfo.FileName = exePath;
            pProcess.StartInfo.Arguments = parameters; //argument
            pProcess.StartInfo.UseShellExecute = false;
            pProcess.StartInfo.RedirectStandardOutput = true;
            pProcess.StartInfo.RedirectStandardError = true;
            pProcess.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            pProcess.StartInfo.CreateNoWindow = true; //not diplay a windows
            pProcess.Start();
            string output = pProcess.StandardOutput.ReadToEnd(); //The output result
            string errput = pProcess.StandardError.ReadToEnd();
            pProcess.WaitForExit();
            ExitCode = pProcess.ExitCode;
            return output;
        }
    }
}