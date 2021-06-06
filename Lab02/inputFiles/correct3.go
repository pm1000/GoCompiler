package main

func y(){

}

func main() {
	var x = 1
	{
	    x = 2
		var x = x + 1
		y()
	}
}