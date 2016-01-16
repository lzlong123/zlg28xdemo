using DevicesApp.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Web.Http;

namespace DevicesApp.Controllers
{
    public class DevicesController : ApiController
    {
        static Device[] devices = new Device[]
        {
            new Device { Id = 1, Name = "Buzzer", State = "OFF" },
            new Device { Id = 2, Name = "Led", State = "OFF" },
            new Device { Id = 3, Name = "Mx280A", State = "OFF" },

        };
        static int Mx280Counter = 0;
        public IEnumerable<Device> GetAlldevices()
        {
            if(Mx280Counter>0)
            {
                Mx280Counter--;
                devices[2].State = "On";
            }
            else
            {
                devices[2].State = "OFF";
            }
            return devices;
        }

        public IHttpActionResult GetDevice(int id)
        {
            var device = devices.FirstOrDefault((p) => p.Id == id);
            if (device == null)
            {
                return NotFound();
            }
            ToggleDevice(id);
            if (id == 3)
            {
                Mx280Counter = 4;
                return Ok(devices);
            }
                
            return Ok(device);
        }

        public void ToggleDevice(int id)
        {
            if (devices[id-1].State == "OFF")
                devices[id-1].State = "ON";
            else
                devices[id-1].State = "OFF";

        }
    }
}
