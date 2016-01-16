transform = function(str)
{
    a = { 
        "-ms-transform":str,
        "-webkit-transform":str,
        "-moz-transform":str,
        "-o-transform":str,
        "transform":str,
    };
    return a;
}

rotate3d2str = function(nv)
{
    
    var str = " rotate3d(";
    str += nv.x + ",";
    str += nv.y + ",";
    str += nv.z + ",";
    str += Math.round(nv.angle*100)/100 + "deg) ";
    return str;
}
translate3d2str = function(x, y, z)
{
    var str = "translate3d(";
    str += x + "px,";
    str += y + "px,";
    str += z + "px)";
    return str
}
rotateAndTranslate = function(obj, nx, ny, nz, x, y, z)
{
    return obj.css(transform(rotate3d2str(Vector.rotate2Axis(0, 0, 1, nx, ny, nz)) + translate3d2str(x, y, z)));
}


//Class PolarVector
{
    function PolarVector(phi, theta, R) {
        this.phi = phi;
        this.theta = theta;
        this.R = R;
        return this;
    }
}


//Class Vector
{
    function Vector(x, y, z) {
        this.x = x;
        this.y = y;
        this.z = z;
        this.angle = 0;
        this.R = 400;
        return this;
    }
    Vector.reverse = function(v)
    {
        v.x = -v.x;
        v.y = -v.y;
        v.z = -v.z;
        v.angle = -v.angle;
        return v;
    }
    Vector.crossAngle = function (v1, v2) {
        var n1 = Math.sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
        var n2 = Math.sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
        var v1timesv2 = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        var cosTheta = v1timesv2 / (n1 * n2);
        var Theta = 180 / Math.PI * Math.acos(cosTheta);
        return Theta;
    }
    Vector.normalVector = function (v1, v2) {
        var nx = v1.y * v2.z - v2.y * v1.z;
        var ny = v1.x * v2.z - v2.x * v1.z;
        var nz = v1.x * v2.y - v2.x * v1.y;
        var v3 = new Vector(nx, ny, nz);
        return v3;
    }
    Vector.rotate2Axis = function (x1, y1, z1, x2, y2, z2) {
        var v1 = new Vector(x1, y1, z1);
        var v2 = new Vector(x2, y2, z2);
        var nv = Vector.normalVector(v1, v2);
        nv.angle = Vector.crossAngle(v1, v2);
        return nv;
    }
    Vector.rotateAxis = function(v, a, axis)
    {
        var rx, ry, rz;
        switch(axis)
        {
            case "X":
                rx = v.x;
                ry = v.y * Math.cos(a) - v.z * Math.sin(a);
                rz = v.y * Math.sin(a) + v.z * Math.cos(a);
                break;
            case "Y":
                rx = v.x * Math.cos(a) + v.z * Math.sin(a);
                ry = v.y;
                rz = -v.x * Math.sin(a) + v.z * Math.cos(a);
                break;
            case "Z":
                rx = v.x * Math.cos(a) - v.y * Math.sin(a);
                ry = v.x * Math.sin(a) + v.y * Math.cos(a);
                rz = v.z;
                break;
            default:
                break;
        }
        var nv = new Vector(rx, ry, rz);
        return nv;
    }
    Vector.toPolar = function(v)
    {
        var r, phi, theta, crossAngle;
        r = Math.sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        phi = Math.atan(v.x / v.y);
        ty = Math.sqrt(v.x * v.x + v.y * v.y);
        theta = Math.atan(ty*v.y/Math.abs(v.y) / v.z);
        if (v.z < 0)
            theta += Math.PI;
        var p = new PolarVector(phi, theta, v.R);
        return p;
    }
}