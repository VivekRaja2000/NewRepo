using System;
using System.Linq;
using System.Collections.Generic;
namespace Firewall
{
    public struct test
    {
        public int a{get;set;}
        internal List<int> temp{get;set;}
    }
    class Program
    {
        static void Main(string[] args)
        {
            test t1=new test();
            t1.a=100;
            
            
            t1.temp=new();
            t1.temp.Add(1);
            
            test t2=t1;
            t2.a=12;
            System.Console.WriteLine(t1.a);
            System.Console.WriteLine(t2.a);
            foreach(var i in t2.temp)
            System.Console.WriteLine(i);
        }
    }
}
