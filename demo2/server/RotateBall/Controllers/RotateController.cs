using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;
using RotateBall.Models;

namespace RotateBall.Controllers
{
    public class RotationsController : ApiController
    {
        static int rotateDegree = 20;
        static Rotate[] rotations = new Rotate[]
        {
            new Rotate { Id = 1, X = 0, Y =0, Z = 20 ,State="OFF"},
            new Rotate { Id = 2, X = 0, Y =90, Z = 0 ,State="OFF"},
            new Rotate { Id = 3, X = 0, Y =0, Z = 90 ,State="OFF"}
        };
        static int Mx280Counter = 0;
        public IEnumerable<Rotate> GetAllRotations()
        {
            if (Mx280Counter > 0)
            {
                Mx280Counter--;
                rotations[0].State = "ON";
            }
            else
            {
                rotations[0].State = "OFF";
                rotations[0].X = 0;
                rotations[0].Y = 0;
                rotations[0].Z = 20;
            }
            return rotations;
        }

        public IHttpActionResult GetRotation(int id)
        {
            switch(id)
            {
                case 1: rotations[0].X =  rotateDegree; rotations[0].Y = 0; break;
                case 2: rotations[0].X = -rotateDegree; rotations[0].Y = 0; break;
                case 3: rotations[0].Y =  rotateDegree; rotations[0].X = 0; break;
                case 4: rotations[0].Y = -rotateDegree; rotations[0].X = 0; break;
                default: break;
            }
            Mx280Counter = 4;
            return Ok(rotations[0]);
        }
    }
}
