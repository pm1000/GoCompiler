package main

func y(){

}

func main() {
	var x = 1
	{
	    //scope 1
	    x = 2
		x = x + 1
		y()
		{
		//scope 2
		    x = x + 1
		}
	}
}