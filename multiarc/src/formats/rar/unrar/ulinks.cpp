
static bool UnixSymlink(const char *Target,const wchar *LinkName,RarTime *ftm,RarTime *fta)
{
  CreatePath(LinkName,true);
  DelFile(LinkName);
  char LinkNameA[NM];
  WideToChar(LinkName,LinkNameA,ASIZE(LinkNameA));
  if (symlink(Target,LinkNameA)==-1) // Error.
  {
    if (errno==EEXIST)
      uiMsg(UIERROR_ULINKEXIST,LinkName);
    else
    {
      uiMsg(UIERROR_SLINKCREATE,UINULL,LinkName);
      ErrHandler.SetErrorCode(RARX_WARNING);
    }
    return false;
  }
#ifdef USE_LUTIMES
  struct timeval tv[2];
  tv[0].tv_sec=fta->GetUnix();
  tv[0].tv_usec=long(fta->GetRaw()%10000000/10);
  tv[1].tv_sec=ftm->GetUnix();
  tv[1].tv_usec=long(ftm->GetRaw()%10000000/10);
  lutimes(LinkNameA,tv);
#endif

  return true;
}


static bool IsFullPath(const char *PathA) // Unix ASCII version.
{
  return *PathA==CPATHDIVIDER;
}


bool ExtractUnixLink30(CommandData *Cmd,ComprDataIO &DataIO,Archive &Arc,const wchar *LinkName)
{
  char Target[NM];
  if (IsLink(Arc.FileHead.FileAttr))
  {
    size_t DataSize=Min(Arc.FileHead.PackSize,ASIZE(Target)-1);
    DataIO.UnpRead((byte *)Target,DataSize);
    Target[DataSize]=0;

    DataIO.UnpHash.Init(Arc.FileHead.FileHash.Type,1);
    DataIO.UnpHash.Update(Target,strlen(Target));
    DataIO.UnpHash.Result(&Arc.FileHead.FileHash);

    // Return true in case of bad checksum, so link will be processed further
    // and extraction routine will report the checksum error.
    if (!DataIO.UnpHash.Cmp(&Arc.FileHead.FileHash,Arc.FileHead.UseHashKey ? Arc.FileHead.HashKey:NULL))
      return true;

    if (!Cmd->AbsoluteLinks && (IsFullPath(Target) ||
        !IsRelativeSymlinkSafe(Arc.FileHead.FileName,Arc.FileHead.RedirName)))
      return false;
    return UnixSymlink(Target,LinkName,&Arc.FileHead.mtime,&Arc.FileHead.atime);
  }
  return false;
}


bool ExtractUnixLink50(CommandData *Cmd,const wchar *Name,FileHeader *hd)
{
  char Target[NM];
  WideToChar(hd->RedirName,Target,ASIZE(Target));
  if (hd->RedirType==FSREDIR_WINSYMLINK || hd->RedirType==FSREDIR_JUNCTION)
  {
    // Cannot create Windows absolute path symlinks in Unix. Only relative path
    // Windows symlinks can be created here. RAR 5.0 used \??\ prefix
    // for Windows absolute symlinks, since RAR 5.1 /??/ is used.
    // We escape ? as \? to avoid "trigraph" warning
    if (strncmp(Target,"\\??\\",4)==0 || strncmp(Target,"/\?\?/",4)==0)
      return false;
    DosSlashToUnix(Target,Target,ASIZE(Target));
  }
  if (!Cmd->AbsoluteLinks && (IsFullPath(Target) ||
      !IsRelativeSymlinkSafe(hd->FileName,hd->RedirName)))
    return false;
  return UnixSymlink(Target,Name,&hd->mtime,&hd->atime);
}
