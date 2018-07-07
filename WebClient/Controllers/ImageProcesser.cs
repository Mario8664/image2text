using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace WebImage2Text.Controllers
{
    public class ImageProcesser
    {
        private static readonly Lazy<ImageProcesser> instance = new Lazy<ImageProcesser>(() => new ImageProcesser());
        private ImageProcesser()
        {
            //Nothing for singleton.
        }
        public static ImageProcesser Instance
        {
            get { return instance.Value; }
        }
        public string GenerateOutputString(string ExePath,string ParamList, out int ExitCode)
        {
            ExitCode = 0;
            string Result = exec(ExePath, ParamList, out ExitCode);
            return Result;
        }
        public int GenerateTxt(string ExePath, string ParamList)
        {
            int ExitCode = 0;
            exec(ExePath, ParamList, out ExitCode);
            return ExitCode;
        }
        public string exec(string ExePath, string parameters, out int ExitCode)
        {
            System.Diagnostics.Process pProcess = new System.Diagnostics.Process();
            pProcess.StartInfo.FileName = ExePath;
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