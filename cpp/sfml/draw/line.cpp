
//Bresenham algorithm credit stackOverflow #10060046
void drawLine(
	sf::Vector2i a,
	sf::Vector2i b,
	int c,sf::RenderTexture& layer,
	sf::Sprite pen){

	int x1=a.x,y1=a.y,x2=b.x,y2=b.y,x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
	dx=x2-x1;
	dy=y2-y1;
	dx1=fabs(dx);
	dy1=fabs(dy);
	px=2*dy1-dx1;
	py=2*dx1-dy1;
	if(dy1<=dx1){
		if(dx>=0){
			x=x1;
			y=y1;
			xe=x2;
		}else{
			x=x2;
			y=y2;
			xe=x1;
		}
		pen.setPosition(x,y);
		layer.draw(pen);
		for(i=0;x<xe;i++){
			x=x+1;
			if(px<0){
				px=px+2*dy1;
			}else{
				if((dx<0 && dy<0) || (dx>0 && dy>0)){
					y=y+1;
				}else{
					y=y-1;
				}
				px=px+2*(dy1-dx1);
			}
			pen.setPosition(x,y);
			layer.draw(pen);
		}
	}else{
		if(dy>=0){
			x=x1;
			y=y1;
			ye=y2;
		}else{
			x=x2;
			y=y2;
			ye=y1;
		}
		pen.setPosition(x,y);
		layer.draw(pen);
		for(i=0;y<ye;i++){
			y=y+1;
			if(py<=0){
				py=py+2*dx1;
			}else{
				if((dx<0 && dy<0) || (dx>0 && dy>0)){
					x=x+1;
				}else{
					x=x-1;
				}
				py=py+2*(dx1-dy1);
			}
		pen.setPosition(x,y);
		layer.draw(pen);
		}
	}
}

