/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author ibrahim
 */
class tcarp extends Thread{
        int procNum;
        int totProc;
        
        //constructor
        tcarp(int p,int tot){
            this.totProc=tot;
            this.procNum=p;
        }
        
        //thread run method
        public void run(int[][] l,int[][] l2,int[][] res,int procNum){
        
        
        int a=l.length*l[0].length;
        int b=l2.length*l2[0].length;
        
        int[][] min;
        int[][] max;
        
        if (a<b){
            min=l;
            max=l2;
        }else{
            min=l2;
            max=l;
        }
        
        if (l[0].length!=l2.length){
            System.out.println("The number of columns in the"
                    + "\nfirst matrix should be equal to the"
                    + "\nnumber of rows in the second!!.");
        }

        for (int x = procNum; x < min.length; x+=totProc) {
            
            for (int t = 0; t < max[0].length; t++) {
                int sum=0;
                
                //ikinci listeyi dikine oku
                for (int i = 0; i < max.length; i++) {
                    
                    /*sum+=min[t][x]*max[i][t];
                    res[i][x]+=sum;*/
                    //System.out.println("res["+x+"]["+i+"]");
                    res[x][t]+=max[i][t]*min[x][i];
                }
            }
        }
    }
}

public class MatrixMultiplication{

    /**
     * @param args the command line arguments
     */
    
    //time-linear sol
    public static int[][] carp(int[][] l,int[][] l2){
        
        
        int a=l.length*l[0].length;
        int b=l2.length*l2[0].length;
        
        int[][] min;
        int[][] max;
        
        if (a<b){
            min=l;
            max=l2;
        }else{
            min=l2;
            max=l;
        }
        
        if (l[0].length!=l2.length){
            System.out.println("The number of columns in the"
                    + "\nfirst matrix should be equal to the"
                    + "\nnumber of rows in the second!!.");
        }
        

        //The number of columns in the first matrix
        //should be equal to the number of rows in the second.
        int [][] res=new int[min.length][max[0].length];
        //
        //min listeyi dikine oku
        //paralelleştirmek için; her işlemci başına 
        //x değeri kadar atlama yapılabilir
        //max.length==min[0].length
        for (int x = 0; x < min.length; x++) {
            
            for (int t = 0; t < max[0].length; t++) {
                int sum=0;
                
                //ikinci listeyi dikine oku
                for (int i = 0; i < max.length; i++) {
                    
                    /*sum+=min[t][x]*max[i][t];
                    res[i][x]+=sum;*/
                    //System.out.println("res["+x+"]["+i+"]");
                    res[x][t]+=max[i][t]*min[x][i];
                }
            }
        }
        
        return res;
    }
    
    public static void decorate(String s,int t){
        for (int i = 0; i < t; i++) {
            System.out.print(s);
        }System.out.println("");
    }
    
    public static void display(String text,int[][]... l){
        System.out.println(text+"\n");
        display(l);
    }
    public static void display(int[][]... l){
        
        //list of arguments list
        for (int i = 0; i < l.length; i++) {
            
            //column of int[][]
            for (int j = 0; j < l[i].length; j++) {
                //rows
                for (int k = 0; k < l[i][j].length; k++) {
                    System.out.printf("%4d",l[i][j][k]);
                }
                System.out.println("");
            }
            System.out.println("");
        }
        /*DEPRECATED
        for (int i = 0; i < l.length; i++) {
            for (int j = 0; j < l[0].length; j++) {
                
                System.out.printf("%4d",l[i][j]);
            }
            System.out.println("");
        }*/
    }
    
    //generate count matrix
    public static int[][] generatemi(int column,int row){
        int[][] result=new int[column][row];
        
        for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {
                result[i][j]=i*row+j;
            }
        }
        return result;
    }
    //generare random matrix on given number range
    public static int[][] generatemr(int column,int row,int range){
        int[][] result=new int[column][row];
        
        for (int i = 0; i < column; i++) {
            for (int j = 0; j < row; j++) {
                result[i][j]=(int) (Math.random()*range);
            }
        }
        return result;
    }
    
    public static void main(String[] args) {
        // TODO code application logic here
        
        double start;
        double end;
        long secToNanosec=1000000000;//1 sec ==10^9 nanosec.
        /*
        int [][] a=generatemi(4,2);
        int[][] b=generatemi(2,3);
        
        display("matrix 1",a);
        display("matrix 2",b);
        
        int[][] sonuc=carp(a,b);
        
        display("matrix of multiplication:",sonuc);
        */
        System.out.println("---------------------\nTRY WITH RANDOM MATRIXES\n");
        int c[][]=generatemr(3,4,10);
        int d[][]=generatemr(4,6,10);
        
        start=System.nanoTime();

        int[][] sonuc2=carp(c,d);
        
        
        display("two random generated matrixes",c,d);
        end=System.nanoTime();
        
        decorate("-",40);
        display("result of matrix multiplication",sonuc2);
        
        double diff1=end-start;
        System.out.println("in "+diff1/secToNanosec+"second(s)");
        decorate("=",40);

        int[][] sonuc3=new int[c.length][d[0].length];
        
        /*
        *
        *same calcultaion with threading concept
        *
        */
        //for efficiency: do not need threads more than matrix column number
        //etkililik için: eşparçacık sayısının matrix sütun sayısından büyük olması gereksiz
        int totProcs=Runtime.getRuntime().availableProcessors();
        System.out.println("calc with "+totProcs+" threads\n");
        //make threads
        
        start=System.nanoTime();
        tcarp[] threads=new tcarp[totProcs];
        for (int i = 0; i < totProcs; i++) {
            threads[i]=new tcarp(i,totProcs);
        }
        
        //start threads
        for (int i = 0; i < totProcs; i++) {
            threads[i].run(c,d,sonuc3,i);
        }
        display(sonuc3);
        end=System.nanoTime();
        
        double diff2=end-start;
        System.out.println("in "+diff2/secToNanosec+"second(s)");
        decorate("-",40);
    }
    
}
