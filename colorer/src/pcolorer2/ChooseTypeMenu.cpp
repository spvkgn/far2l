#include "ChooseTypeMenu.h"

ChooseTypeMenu::ChooseTypeMenu(const wchar_t *AutoDetect,const wchar_t *Favorites)
{
  ItemCount = 0;
  Item = nullptr;
  ItemSelected = 0;

  UnicodeString s("&A ");
  s.append(AutoDetect);
  AddItem(s.getWChars(), MIF_NONE, nullptr, 0);
  AddItem(Favorites, MIF_SEPARATOR, nullptr, 1);
}

ChooseTypeMenu::~ChooseTypeMenu()
{
  for (size_t idx = 0; idx < ItemCount; idx++){
    if (Item[idx].Text){
      free((void*) Item[idx].Text);
    }
  }
  free(Item);
}

void ChooseTypeMenu::DeleteItem(size_t index)
{
  if (Item[index].Text){
    free((void*) Item[index].Text);
  }
  memmove(Item+index,Item+index+1,sizeof(FarMenuItemEx)*(ItemCount-(index+1)));
  ItemCount--;
  if (ItemSelected>=index) ItemSelected--;
}

FarMenuItemEx *ChooseTypeMenu::getItems()
{
  return Item;
}

int ChooseTypeMenu::AddItem(const wchar_t *Text, const MENUITEMFLAGS Flags, const FileType* UserData, size_t PosAdd)
{
  if (PosAdd > ItemCount)
    PosAdd = ItemCount;

  if (!(ItemCount & 255))
  {
    FarMenuItemEx *NewPtr;
    if (!(NewPtr=(FarMenuItemEx *)realloc(Item, sizeof(FarMenuItemEx)*(ItemCount+256+1))))
      return -1;

    Item=NewPtr;
  }

  if (PosAdd < ItemCount)
    memmove(Item+PosAdd+1,Item+PosAdd,sizeof(FarMenuItemEx)*(ItemCount-PosAdd));

  ItemCount++;

  Item[PosAdd].Flags = Flags;
  Item[PosAdd].Text = _wcsdup(Text);
  Item[PosAdd].UserData = (DWORD_PTR) UserData;
  Item[PosAdd].Reserved = 0;
  Item[PosAdd].AccelKey = 0;

  return PosAdd;
}

int ChooseTypeMenu::AddGroup(const wchar_t *Text)
{
  return AddItem(Text, MIF_SEPARATOR, nullptr);
}

int ChooseTypeMenu::AddItem(const FileType* fType, size_t PosAdd)
{
  UnicodeString *s=GenerateName(fType);
  size_t k=AddItem(s->getWChars(), MIF_NONE, fType, PosAdd);
  delete s;
  return k;
}

void ChooseTypeMenu::SetSelected(size_t index)
{
  if (index<ItemCount){
    Item[ItemSelected].Flags &= ~MIF_SELECTED;
    Item[index].Flags |= MIF_SELECTED;
    ItemSelected =index;
  }
}

int ChooseTypeMenu::GetNext(size_t index)
{
  size_t p;
  for (p=index+1;p<ItemCount;p++){
    if (!(Item[p].Flags &MIF_SEPARATOR)) break;
  }
  if (p<ItemCount){
    return p;
  }else{
    for (p=favorite_idx; p<ItemCount && !(Item[p].Flags&MIF_SEPARATOR);p++);
    return p+1;
  }
}

FileType* ChooseTypeMenu::GetFileType( size_t index)
{
  return (FileType*)Item[index].UserData;
}

void ChooseTypeMenu::MoveToFavorites(size_t index)
{
  FileType* f=(FileType*)Item[index].UserData;
  DeleteItem(index);
  size_t k=AddFavorite(f);
  SetSelected(k);
  HideEmptyGroup();
}

int ChooseTypeMenu::AddFavorite(const FileType* fType)
{
  size_t i;
  for (i=favorite_idx;i<ItemCount && !(Item[i].Flags&MIF_SEPARATOR);i++);
  size_t p=AddItem(fType,i=ItemCount?i:i+1);
  if (ItemSelected>=p) ItemSelected++;
  return p;
}

void ChooseTypeMenu::HideEmptyGroup()
{
  for (size_t i=favorite_idx;i<ItemCount-1;i++){
    if ((Item[i].Flags&MIF_SEPARATOR)&&(Item[i+1].Flags&MIF_SEPARATOR)) Item[i].Flags|=MIF_HIDDEN;
  }
}

void ChooseTypeMenu::DelFromFavorites(size_t index)
{
  FileType* f=(FileType*)Item[index].UserData;
  DeleteItem(index);
  AddItemInGroup(f);
  if (Item[index].Flags&MIF_SEPARATOR)  SetSelected(GetNext(index));
  else  SetSelected(index);
  f->setParamValue(DFavorite,&DFalse);
}

int ChooseTypeMenu::AddItemInGroup(FileType* fType)
{
  size_t i;
  auto group =fType->getGroup();
  for (i = favorite_idx; i < ItemCount && !((Item[i].Flags & MIF_SEPARATOR) &&
       (group.compare(UnicodeString((wchar*)Item[i].Text)) == 0)); i++);
  if (Item[i].Flags & MIF_HIDDEN) Item[i].Flags &= ~MIF_HIDDEN;
  size_t k = AddItem(fType, i + 1);
  if (ItemSelected >= k) ItemSelected++;
  return k;
}

bool ChooseTypeMenu::IsFavorite(size_t index)
{
  size_t i;
  for (i=favorite_idx;i<ItemCount && !(Item[i].Flags&MIF_SEPARATOR);i++);
  i=ItemCount?i:i+1;
  if (i>index) return true;
  return false;
}

void ChooseTypeMenu::RefreshItemCaption(size_t index)
{
  if (Item[index].Text){
    free((void*) Item[index].Text);
  }

  UnicodeString *s=GenerateName(GetFileType(index));
  Item[index].Text= _wcsdup(s->getWChars());
  delete s;
}

UnicodeString* ChooseTypeMenu::GenerateName(const FileType* fType)
{
  const UnicodeString *v;
  v=fType->getParamValue(DHotkey);
  auto* s=new UnicodeString;
  if (v && v->length()){
    s->append("&").append(*v);
  }else{
    s->append(" ");
  }
  s->append(" ").append(fType->getDescription());

  return s;
}
