{"filter":false,"title":"resize.c","tooltip":"~/workspace/resize.c","undoManager":{"mark":22,"position":22,"stack":[[{"start":{"row":0,"column":0},"end":{"row":0,"column":1},"action":"insert","lines":["#"],"id":1}],[{"start":{"row":0,"column":1},"end":{"row":0,"column":2},"action":"insert","lines":["<"],"id":2},{"start":{"row":0,"column":2},"end":{"row":0,"column":3},"action":"insert","lines":["s"]},{"start":{"row":0,"column":3},"end":{"row":0,"column":4},"action":"insert","lines":["t"]},{"start":{"row":0,"column":4},"end":{"row":0,"column":5},"action":"insert","lines":["d"]}],[{"start":{"row":0,"column":5},"end":{"row":0,"column":6},"action":"insert","lines":["i"],"id":3},{"start":{"row":0,"column":6},"end":{"row":0,"column":7},"action":"insert","lines":["n"]}],[{"start":{"row":0,"column":6},"end":{"row":0,"column":7},"action":"remove","lines":["n"],"id":4}],[{"start":{"row":0,"column":6},"end":{"row":0,"column":7},"action":"insert","lines":["o"],"id":5},{"start":{"row":0,"column":7},"end":{"row":0,"column":8},"action":"insert","lines":["."]},{"start":{"row":0,"column":8},"end":{"row":0,"column":9},"action":"insert","lines":["h"]}],[{"start":{"row":0,"column":9},"end":{"row":0,"column":10},"action":"insert","lines":[">"],"id":6}],[{"start":{"row":0,"column":10},"end":{"row":1,"column":0},"action":"insert","lines":["",""],"id":7},{"start":{"row":1,"column":0},"end":{"row":2,"column":0},"action":"insert","lines":["",""]}],[{"start":{"row":2,"column":0},"end":{"row":2,"column":1},"action":"insert","lines":["i"],"id":8},{"start":{"row":2,"column":1},"end":{"row":2,"column":2},"action":"insert","lines":["n"]},{"start":{"row":2,"column":2},"end":{"row":2,"column":3},"action":"insert","lines":["t"]}],[{"start":{"row":2,"column":3},"end":{"row":2,"column":4},"action":"insert","lines":[" "],"id":9},{"start":{"row":2,"column":4},"end":{"row":2,"column":5},"action":"insert","lines":["m"]},{"start":{"row":2,"column":5},"end":{"row":2,"column":6},"action":"insert","lines":["a"]},{"start":{"row":2,"column":6},"end":{"row":2,"column":7},"action":"insert","lines":["i"]},{"start":{"row":2,"column":7},"end":{"row":2,"column":8},"action":"insert","lines":["n"]}],[{"start":{"row":2,"column":8},"end":{"row":2,"column":9},"action":"insert","lines":["{"],"id":10}],[{"start":{"row":2,"column":9},"end":{"row":4,"column":1},"action":"insert","lines":["","    ","}"],"id":11}],[{"start":{"row":3,"column":0},"end":{"row":3,"column":4},"action":"remove","lines":["    "],"id":12},{"start":{"row":2,"column":9},"end":{"row":3,"column":0},"action":"remove","lines":["",""]}],[{"start":{"row":2,"column":8},"end":{"row":3,"column":0},"action":"insert","lines":["",""],"id":13}],[{"start":{"row":4,"column":0},"end":{"row":6,"column":0},"action":"insert","lines":["","    ",""],"id":14}],[{"start":{"row":2,"column":8},"end":{"row":3,"column":0},"action":"remove","lines":["",""],"id":15}],[{"start":{"row":2,"column":8},"end":{"row":3,"column":0},"action":"insert","lines":["",""],"id":16}],[{"start":{"row":0,"column":0},"end":{"row":6,"column":1},"action":"remove","lines":["#<stdio.h>","","int main","{","","    ","}"],"id":17},{"start":{"row":0,"column":0},"end":{"row":99,"column":0},"action":"insert","lines":["// Copies a BMP file","","#include <stdio.h>","#include <stdlib.h>","","#include \"bmp.h\"","","int main(int argc, char *argv[])","{","    // ensure proper usage","    if (argc != 3)","    {","        fprintf(stderr, \"Usage: copy infile outfile\\n\");","        return 1;","    }","","    // remember filenames","    char *infile = argv[1];","    char *outfile = argv[2];","","    // open input file","    FILE *inptr = fopen(infile, \"r\");","    if (inptr == NULL)","    {","        fprintf(stderr, \"Could not open %s.\\n\", infile);","        return 2;","    }","","    // open output file","    FILE *outptr = fopen(outfile, \"w\");","    if (outptr == NULL)","    {","        fclose(inptr);","        fprintf(stderr, \"Could not create %s.\\n\", outfile);","        return 3;","    }","","    // read infile's BITMAPFILEHEADER","    BITMAPFILEHEADER bf;","    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);","","    // read infile's BITMAPINFOHEADER","    BITMAPINFOHEADER bi;","    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);","","    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0","    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||","        bi.biBitCount != 24 || bi.biCompression != 0)","    {","        fclose(outptr);","        fclose(inptr);","        fprintf(stderr, \"Unsupported file format.\\n\");","        return 4;","    }","","    // write outfile's BITMAPFILEHEADER","    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);","","    // write outfile's BITMAPINFOHEADER","    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);","","    // determine padding for scanlines","    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;","","    // iterate over infile's scanlines","    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)","    {","        // iterate over pixels in scanline","        for (int j = 0; j < bi.biWidth; j++)","        {","            // temporary storage","            RGBTRIPLE triple;","","            // read RGB triple from infile","            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);","","            // write RGB triple to outfile","            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);","        }","","        // skip over padding, if any","        fseek(inptr, padding, SEEK_CUR);","","        // then add it back (to demonstrate how)","        for (int k = 0; k < padding; k++)","        {","            fputc(0x00, outptr);","        }","    }","","    // close infile","    fclose(inptr);","","    // close outfile","    fclose(outptr);","","    // success","    return 0;","}",""]}],[{"start":{"row":0,"column":3},"end":{"row":0,"column":9},"action":"remove","lines":["Copies"],"id":18},{"start":{"row":0,"column":3},"end":{"row":0,"column":4},"action":"insert","lines":["r"]},{"start":{"row":0,"column":4},"end":{"row":0,"column":5},"action":"insert","lines":["e"]},{"start":{"row":0,"column":5},"end":{"row":0,"column":6},"action":"insert","lines":["s"]},{"start":{"row":0,"column":6},"end":{"row":0,"column":7},"action":"insert","lines":["i"]},{"start":{"row":0,"column":7},"end":{"row":0,"column":8},"action":"insert","lines":["z"]},{"start":{"row":0,"column":8},"end":{"row":0,"column":9},"action":"insert","lines":["e"]},{"start":{"row":0,"column":9},"end":{"row":0,"column":10},"action":"insert","lines":["d"]}],[{"start":{"row":0,"column":9},"end":{"row":0,"column":10},"action":"remove","lines":["d"],"id":19}],[{"start":{"row":0,"column":9},"end":{"row":0,"column":10},"action":"insert","lines":["s"],"id":20}],[{"start":{"row":10,"column":16},"end":{"row":10,"column":17},"action":"remove","lines":["3"],"id":21}],[{"start":{"row":10,"column":16},"end":{"row":10,"column":17},"action":"insert","lines":["4"],"id":22}],[{"start":{"row":12,"column":25},"end":{"row":12,"column":51},"action":"remove","lines":["Usage: copy infile outfile"],"id":24},{"start":{"row":12,"column":25},"end":{"row":12,"column":57},"action":"insert","lines":["Usage: ./resize n infile outfile"]}]]},"ace":{"folds":[],"scrolltop":0,"scrollleft":0,"selection":{"start":{"row":27,"column":0},"end":{"row":27,"column":0},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":0},"timestamp":1546530357588,"hash":"9e1c83c9aba9049e15e2ccf45c96bc7be80c70ee"}