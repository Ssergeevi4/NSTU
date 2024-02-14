program main
        implicit double precision (a-h, o-z)
        common /partition/ lines
        common /interval/ a, b, step 
        
    
        dimension memory(100000000) ! 100 000 000
        
        call readdata()
        call makepartition(memory(1))
        
        result_5 = rectangle(memory(1))
        result_6 = simpson(memory(1))
                
        
        print *, 'rectangle: ', result_5
        print *, 'simpson: ', result_6
        print *, ' '
        pause

        end
      
******functions_definition
        double precision function fun(x)
        implicit double precision (a-h, o-z)
!        tmp = x
!        tmp = tmp * sin(3*x)
!        tmp = tpm * 3*x
        fun = x *SIN(3*x)
        end
      
        subroutine readdata()
        implicit double precision (a-h, o-z)
        common /partition/ lines
        common /interval/ a, b, step 
        
        open(1, file='C://ProgFor/input4_1.txt',err = 1)
        read(1, *) a, b, lines
        close(1)
        
        if (lines .eq. 0.0) goto 3
        
        step = (b - a) / lines
      
        print *, 'input data reading success.'
        return  
1       pause 'input error: "input.txt" file does not exist!'
        stop 
3       pause 'input error: zero steps!'
        stop
        end
        
        subroutine makepartition(partition)
        implicit double precision (a-h, o-z)
        common /partition/ lines
        common /interval/ a, b, step 
        
        dimension partition(*)
        
        do i = 0, lines
          partition(i + 1) = a + i * step
        end do
        if (partition(lines) .ne. b) then
          lines = lines + 1
          partition(lines) = b
        end if
        
        print *, 'partition created.'
        return  
        end
        
        
        
        double precision function rectangle(partition)
        implicit double precision (a-h, o-z)
        integer n
        
        common /partition/ lines
        common /interval/ a, b, step 
        
        n=lines 
        
        dx=(b-a)/n
        x=a+(dx/2.0)
        
        do i=1,n
        
        sum=sum+(fun(x))
        x=x+dx
        end do
        rectangle = dx*sum
        end
        
        
        

        double precision function simpson(partition)
        implicit double precision (a-h, o-z)
        integer n
        
        common /partition/ lines
        common /interval/ a, b, step 
!        dimension partition(*)        
        n=lines 
        if(mod(n,2).eq.1)n=n+1
        dx=(b-a)/n
!        print *, dx
!        read(*,*)
        x=a 
        sum=fun(x)
        
        do i = 1, n-1
        x=a+i*dx
          tmp_sum=(fun(x))
          if(mod(i,2).eq.1)then
          tmp_sum=tmp_sum*4
          else
          tmp_sum=tmp_sum*2
          end if
          
          sum=sum+tmp_sum
        end do
        sum=sum+fun(b)
        sum=sum*dx/3

        simpson = sum
        end
