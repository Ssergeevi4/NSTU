program main
100   format(i12\)
      write(*,*) 'enter n m'
      read*, n  
      
      open(31,file='diag1.dir' ,access='direct',recl=4)
      open(32,file='diag2.dir' ,access='direct',recl=4)
      open(33,file='diag3.dir' ,access='direct',recl=4)
 
      open(35,file='vec.dir'   ,access='direct',recl=4)
      open(36,file='sizes.txt')
      m = 1
      do i=1,n
        write(31, rec=i) 0.25*i
      end do
      do i=1,n-1
        write(32, rec=i) 0.25*i
      end do
      do i=1,n-2-m
        write(33, rec=i) 0.25
      end do

      
      do i=1,n
        write(35, rec=i) 0.25*i
      end do
      write(36,100) n, m
      write(*,*) 'ok'
      read*
      end
	  
	  
	  
  Умножение матрицы на вектор
        program main
        common/sizes/n,m
        
        dimension arr(100000000)
        max=100000000
        open(1, file='sizes.txt')
        read (1,*) n, m
        
        i_vec_off = n*4+1
        i_res_off = i_vec_off+n+1
        call input_from_dir(arr, arr(i_vec_off))
        call mul(arr, arr(i_vec_off), arr(i_res_off))
        
        
        read*
      end
      
    
      
      subroutine input(f_matrix, vec)
      common/sizes/n,m
      dimension f_matrix(*)
      dimension vec(*)
      open(21, file='diag1.txt')
      open(22, file='diag2.txt')
      open(23, file='diag3.txt')

      open(25, file='vec.txt')
   
      read(21, *) (f_matrix(i+0*n), i=1, n)
      read(22, *) (f_matrix(i+1*n), i=1, n-1)
      read(23, *) (f_matrix(i+2*n), i=1, n-2-m)
   
      read(25, *) (vec(i), i=1, n)
      
      close(21)
      close(22)
      close(23)
      close(24)
      close(25)
      end
      
      subroutine input_from_dir(f_matrix, vec)
      common/sizes/n,m
      dimension f_matrix(*)
      dimension vec(*)
      open(21, file='diag1.dir', access='direct', recl=4)
      open(22, file='diag2.dir', access='direct', recl=4)
      open(23, file='diag3.dir', access='direct', recl=4)
      open(25, file='vec.dir', access='direct', recl=4)
    
      do i =1,n
        read(21, rec=i) f_matrix(i+0*n)
      end do
      do i =1,n-1
        read(22, rec=i) f_matrix(i+1*n)
      end do
      do i =1,n-2-m
        read(23, rec=i) f_matrix(i+2*n)
      end do

      do i =1,n
        read(25, rec=i) vec(i+0*n)
      end do
  
      
      close(21)
      close(22)
      close(23)
      close(24)
      close(25)
      end
      
      subroutine mul(f_matrix, vec, res)
      common/sizes/n,m
      dimension f_matrix(*)
      dimension vec(*)
      dimension res(*)
   
      do i=1,n
        res(i) =res(i)+ f_matrix(i)*vec(i)
      end do
      do i=1,n-1
        res(i) =res(i)+ f_matrix(n+i)*vec(i+1)
        res(i+1)=res(i+1)+f_matrix(n+i)*vec(i)
      end do
      
      do i=1,n-2-m
        res(i) =res(i)+ f_matrix(n*2+i)*vec(i+2+m)
        res(i+2+m)=res(i+2+m)+f_matrix(n*2+i)*vec(i)
      end do
 
      write(*, *) 'ok'
      
      do i=1,n
          write(*, *)res(i)
      end do
        
      end

 Перевод текстовой матрицы в прямой
       program main
      common/sizes/n,m
      dimension arr(100000000)
        max=100000000
    
      
      open(20, file='sizes.txt')
      
      read(20,*)n, m
      i_vec_off = n*4
      i_res_off = i_vec_off+n
      call input(arr, arr(i_vec_off))
      call to_dir(arr, arr(i_vec_off))
      end
      
      subroutine input(f_matrix, vec)
      common/sizes/n,m
      dimension f_matrix(*)
      dimension vec(*)
      open(21, file='diag1.txt')
      open(22, file='diag2.txt')
      open(23, file='diag3.txt')
 
      open(25, file='vec.txt')
   
      read(21, *) (f_matrix(i+0*n), i=1, n)
      read(22, *) (f_matrix(i+1*n), i=1, n-1)
      read(23, *) (f_matrix(i+2*n), i=1, n-2-m)
 
      read(25, *) (vec(i), i=1, n)
      
      close(21)
      close(22)
      close(23)

      close(25)
      end
      
      subroutine to_dir(f_matrix, vec)
      common/sizes/n,m
      dimension f_matrix(*)
      dimension vec(*)
   
      open(31,file='diag1.dir' ,access='direct',recl=4)
      open(32,file='diag2.dir' ,access='direct',recl=4)
      open(33,file='diag3.dir' ,access='direct',recl=4)

      open(35,file='vec.dir' ,access='direct',recl=4)
      
      do i=1,n
        write(31,rec=i)f_matrix(i+0*n)
      end do
      
      do i=1,n-1
        write(32,rec=i)f_matrix(i+1*n)
      end do
      
      do i=1,n-2-m
        write(33,rec=i)f_matrix(i+2*n)
      end do

      
      do i=1,n
        write(35,rec=i)vec(i)
      end do
      
      close(31)
      close(32)
      close(33)

      close(35)
      end
