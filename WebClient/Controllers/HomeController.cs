using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using WebImage2Text.Models;
using Microsoft.Extensions.Options;


namespace WebImage2Text.Controllers
{
    public class HomeController : Controller
    {

        private AppSettings AppSettings { get; set; }

        public HomeController(IOptions<AppSettings> settings)
        {
            AppSettings = settings.Value;
        }
        public IActionResult Image2Text()
        {
            return View();
        }
        [HttpPost("UploadImage")]
        public IActionResult UploadImage([FromServices]IHostingEnvironment env, List<IFormFile> SourceImage, ImageViewModel Model)
        { 
            // full path to file in temp location
            var filePath = env.WebRootPath + "/upload/"+DateTime.Now.ToString("MMddHHmmss") + "."+ SourceImage.First().FileName.Split('.').Last();

            foreach (var formFile in SourceImage)
            {
                if (formFile.Length > 0)
                {
                    using (var stream = new FileStream(filePath, FileMode.Create))
                    {
                        formFile.CopyTo(stream);
                    }
                }
            }
            string Param = "--source={0} --scalex={1} --scaley={2} --type={3}";
            Param=String.Format(Param,filePath,Model.ScaleX, Model.ScaleY, 1);
            ViewData["Result"]=exec(AppSettings.ExecuteFileName,Param);
            if(System.IO.File.Exists(filePath)) System.IO.File.Delete(filePath);
            return View("Result");
        }
        private string exec(string exePath, string parameters)
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
            return output;
        }
    }
}