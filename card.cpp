#include<iostream>
#include"card.h"
#include"console.h"
#include"enemy.h"

extern int cardPrintX,cardPrintY;

void print(Card card)
{
    if (card.rarity==1) setcolor("white");
    if (card.rarity==2) setcolor("green");
    if (card.rarity==3) setcolor("blue");
    if (card.rarity==4) setcolor("purple");
    if (card.rarity==5) setcolor("red");
    print(card.description,cardPrintX,cardPrintY);
}
void AttackCard::effect(Enemy enemy)
{
    
}