using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RotateBall.Models
{
    public class Rotate
    {
        public int Id { get; set; }
        public int X { get; set; }
        public int Y { get; set; }
        public int Z { get; set; }
        public string State { get; set; }
    }
}