program main
                
        real min_x, max_x, step_x, min_y, max_y, step_y, i, j,x,y
        integer steps_x, steps_y
        logical IsSame
        OPEN (1,FILE='C:\Users\Sergeevi4\Desktop\Input.txt')
        OPEN (2,FILE='C:\Users\Sergeevi4\Desktop\Output.txt') 
        
        read (1,*) min_x 
        read (1,*) max_x
        read (1,*) step_x
        read (1,*) min_y
        read (1,*) max_y
        read (1,*) step_y
        
        call around(min_x,min_x)
        call around(min_y,min_y)
        call around(max_x,max_x)                
        call around(max_y,max_y)        
        call around(step_x,step_x)
        call around(step_y,step_y)
        
        if((min_x .GT. max_x) .OR. (min_y .GT. max_y) )then
        write(2,'(A)') 'Data entered incorrectly' 
        else if(step_x*step_y .EQ. 0) then
        write(2,'(A)') 'Data entered incorrectly' 
        else
        
        
        x = -min_x-1
        y = -min_y-1
                
        steps_x = (max_x-min_x)/step_x
        steps_y = (max_y-min_y)/step_y       
        write(2,'(A$)') '             | '
        
        do i = 0, steps_x            
           if(IsSame(x,min_x + i*step_x)) then    
               x = min_x + i*step_x      
               write(2,'(e12.4$,(A$))') x, ' | '  
           end if              
        end do
        call around(x,x)        
        if(x .LT. max_x) then
            write(2,'(e12.4$, (A$))') max_x, ' | '
        end if     
        
        write (2,*) ' '
        
        do i = 0, steps_y
            if(IsSame(y,min_y+i*step_y)) then 
               y = min_y + i*step_y
               write(2,'(e12.4$,(A$))') y, ' | '          
            
            x = -min_x-1
            do j = 0, steps_x
                if(IsSame(x,min_x + j*step_x)) then 
                    x = min_x + j*step_x                
                    call func(x,y)
                end if
            end do 
            call around(x,x)
            if(x .LT. max_x) then
                call Func(max_x,y)
            end if
            
            write (2,*) ' '
            end if
                                   
        end do
        
        
        call around(y,y)
        if(y .LT. max_y) then
                    write(2,'(e12.4$,(A$))') max_y, ' | '
                    y = max_y
                    x = -min_x-1
                    do j = 0, steps_x
                        if(IsSame(x,min_x + j*step_x)) then 
                            x = min_x + j*step_x                
                            call func(x,y)                     
                        end if
                    end do 
            
                    if(x .LT. max_x) then
                        call Func(max_x,y)
                    end if
            end if
        end if   
        end 
        
        subroutine Func(x, y) 
            implicit none  
            real x,y,yt,xt,Pi
            parameter(pi = 3.1415926535)
            call Around(y+90.0,yt) 
            call Around(x,xt) 
            if (mod(yt,180.0) .EQ. 0.0) then
                write(2, '(A$)') '  div. by 0  | '      
            else if(mod(xt,180.0) .EQ. 0.0) then
                write(2, '(A$)') '      0      | '
            else 
            call around(x,x)
            call around(sin(x*PI/180.0),xt)
            call around(cos(y*PI/180.0),yt)
      write(2,'(e12.4$, A$)')abs(xt/yt),' | '                 
            end if   
                      
            return
        end
        
               
                  
                 logical function IsSame(x,y)
                 implicit none
                 real x,y
                 call Around(x,x)
                 call Around(y,y)

                 if(x .EQ. y) then
                    IsSame = .FALSE.
                    return
                 else
                    IsSame = .TRUE.             
                    return
                  end if
                  end
                
                
                
                
                subroutine Around(x,result)
                implicit none
                real x, result 
                character*12 line
                write(line,'(e12.4)') x
                read(line,'(e12.4)')result           
                end
