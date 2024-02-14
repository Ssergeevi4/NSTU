subroutine InputCoordinates
      common/block/ a, b, c, S, betta, Angle, pi, fi
      read*, a, c, betta 
      print*, 'A=', a
      print*, 'C=', c
      print*, 'Betta=', betta
      end
      
      subroutine AreaCalculation
      common/block/ a, b, c, S, betta, Angle, pi, fi
      Angle= betta*pi/180
      S=0.5*a*c*sin(Angle)
      print*, 'Area of triangle:', S
      end
      
      subroutine SerchMinAngle
      common/block/ a, b, c, S, betta, Angle, pi, fi
      b=sqrt(a*a+c*c-2*a*c*cos(Angle))
      print*, 'Unknown Side:', b
      if(a .LE. b .AND. a .LE. c) fi = (b**2 + c**2 - a**2)/(2*b*c)
      if(b .LE. a .AND. b .LE. c) fi = (a**2 + c**2 - b**2)/(2*a*c)
      if(c .LE. a .AND. c .LE. b) fi = (a**2 + b**2 - c**2)/(2*a*b)
      fi = acos(fi)*180/pi
      print*, 'Min Angle: ', fi
      end
      
      subroutine CosMinAngle
      common/block/ a, b, c, S, betta, Angle, pi, fi, fi2
      fi2= fi*pi/180
      cosfi = cos(fi2*pi/180)
      print*, 'Min Angle Cos', cosfi
      end
           
      subroutine Menu
      print*, '   '
      print*, '                Menu'
      print*, '1) Entering a new triangle'
      print*, '2) Calculating the area of a triangle'
      print*, '3) Calculating the minimum angle in degrees'
      print*, '4) Calculating the cos os the minimum angle'
      print*, '5) End of work'
      print*, '   '
      end

      program main
      common/block/ a, b, c, S, betta, Angle, pi, fi
      pi = 3.1415926536
1     call Menu
      read*, k
      select case (k)
      case (1)
      call InputCoordinates
      case (2)
      call AreaCalculation
      case (3)
      call SerchMinAngle
      case (4)
      call CosMinAngle
      case (5)
      go to 2 
      case default
      print*, 'Error. Select a command from 1 to 5'      
      end select
      go to 1
2     end
