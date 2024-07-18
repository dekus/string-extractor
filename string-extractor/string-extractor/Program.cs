using System;

using System.IO;

using System.Security.Cryptography;

using PeNet;

namespace StringExtractor

{
    class Program
   
    {
        static void Main(string[] args)
       
        {
            if (args.Length > 0)
            
            {

                string peFile = args[0];

                if (!File.Exists(peFile))
                
                {
                   
                    Console.WriteLine("File not found.");
                
                    return;
                
                }

                ExtractStrings(peFile);
            
                Console.WriteLine("Strings extracted successfully!");
            
            }
            
            else
            
            {
        
                Console.WriteLine("Drag and drop a .exe file onto this application to extract its strings.");
            
            }
        }

        static void ExtractStrings(string peFilePath)
        
        {
            string fileName = Path.GetFileNameWithoutExtension(peFilePath);
            
            string txtName = fileName + "result.txt";

            using (StreamWriter file = new StreamWriter(txtName))
            
            {
                string fileName2 = Path.GetFileName(peFilePath);
                
                file.WriteLine("File Name: " + fileName2);

                long fileSize = new FileInfo(peFilePath).Length;
                
                file.WriteLine("File Size: " + fileSize + " bytes");

                var pe = new PeFile(peFilePath);

                if (pe != null)
                
                {
                    using (var md5 = MD5.Create())
                    
                    {
                        
                        byte[] md5Hash = md5.ComputeHash(File.ReadAllBytes(peFilePath));
                    
                        string md5String = BitConverter.ToString(md5Hash).Replace("-", "").ToLower();
                        
                        file.WriteLine("MD5: " + md5String);
                    
                    }

                    if (pe.ImageNtHeaders != null)
                   
                    {
                        string pcasvcString = "0x" + pe.ImageNtHeaders.OptionalHeader.SizeOfImage.ToString("X");

                        file.WriteLine("PcaSvc: " + pcasvcString);

                    }

                    else

                    {

                        Console.WriteLine("ImageNtHeaders is null.");

                    }

                    if (pe.ImageNtHeaders?.FileHeader != null)

                    {
                        int timestamp = (int)pe.ImageNtHeaders.FileHeader.TimeDateStamp;

                        DateTime timestampDt = DateTimeOffset.FromUnixTimeSeconds(timestamp).UtcDateTime;

                        string timestampStr = timestampDt.ToString("yyyy/MM/dd:HH:mm:ss");

                        string dpsString = "!" + timestampStr;

                        file.WriteLine("DPS: " + dpsString);
                    }

                    else

                    {
                        Console.WriteLine("FileHeader or TimeDateStamp is null.");
                    }
                }

                else

                {
                    Console.WriteLine("PeFile instance is null.");
                }
            }
        }
    }
}
