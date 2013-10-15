/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2013  Gianni Rossi <gianni.rossi@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "rmreqprojects.h"
#include "redminemanager.h"

#include <QJsonArray>
#include <boost/concept_check.hpp>

RMReqProjects::RMReqProjects(RedMineManager* manager): 
    RMRequest(manager)
{

}

QUrl RMReqProjects::buildUrl()
{
    QUrl result(m_manager->baseUrl());
    result.setPath("/projects.json");
    return result;
}

void RMReqProjects::replyFinished(QNetworkReply* reply)
{
    RMRequest::replyFinished(reply);
    
    if (m_jsonDocument.isArray())
    {
        for(auto project : m_jsonDocument.array())
        {
            //"{"projects":[{"created_on":"2012/12/19 11:31:00 -0200","identifier":"bitforge_project","updated_on":"2012/12/19 11:31:00 -0200","name":"Bit Forge Project","id":18,"description":""},{"created_on":"2013/03/15 10:58:54 -0300","identifier":"libbf","updated_on":"2013/03/15 10:58:54 -0300","name":"libbf","parent":{"name":"Bit Forge Project","id":18},"id":24,"description":"Biblioteca de utilidades da BF."},{"created_on":"2012/12/19 11:44:06 -0200","identifier":"bitforge_metodologia","updated_on":"2012/12/19 11:44:06 -0200","name":"Metodologia de Trabalho","parent":{"name":"Bit Forge Project","id":18},"id":19,"description":""},{"created_on":"2012/12/19 11:47:41 -0200","identifier":"bitforge_padrao_codigo","updated_on":"2012/12/19 11:47:41 -0200","name":"Padr\u00e3o de Codifica\u00e7\u00e3o","parent":{"name":"Bit Forge Project","id":18},"id":20,"description":""},{"created_on":"2012/12/11 21:58:37 -0200","identifier":"cracha","updated_on":"2012/12/11 21:58:37 -0200","name":"Crach\u00e1","id":14,"description":"Pagamento nas rede BR com vale fornecido pela Petrobr\u00e1s."},{"created_on":"2013/02/20 06:50:56 -0300","identifier":"cracha_analise_bandas","updated_on":"2013/02/20 06:50:56 -0300","name":"Crach\u00e1 - Analisador de Bandas","parent":{"name":"Crach\u00e1","id":14},"id":21,"description":"Projeto em Android com o objetivo de analisar o que for poss\u00edvel referente as bandas de celular e enviar essa informa\u00e7\u00e3o para uma central."},{"created_on":"2012/12/11 21:59:22 -0200","identifier":"cracha_android","updated_on":"2012/12/11 21:59:22 -0200","name":"Crach\u00e1 - Android","parent":{"name":"Crach\u00e1","id":14},"id":15,"description":"M\u00f3dulo client - executado em Android"},{"created_on":"2012/12/11 22:00:17 -0200","identifier":"cracha_mock","updated_on":"2012/12/11 22:00:17 -0200","name":"Crach\u00e1 - Mock","parent":{"name":"Crach\u00e1","id":14},"id":16,"description":"M\u00f3dulo Mock server que realiza a ponte em TCP/IP entre o Crach\u00e1 Android e Crach\u00e1 Server"},{"created_on":"2012/12/11 22:02:13 -0200","identifier":"cracha_server","updated_on":"2012/12/11 22:02:13 -0200","name":"Crach\u00e1 Server","parent":{"name":"Crach\u00e1","id":14},"id":17,"description":"Crach\u00e1 Server - Executado em JBoss AS 7.1.1 ou superior"},{"created_on":"2013/05/09 16:48:17 -0300","identifier":"syscred_credirede","updated_on":"2013/05/13 11:15:39 -0300","name":"CrediRede","id":25,"description":"O Sistema Esteira de Credito e formado por um conjunto de M\u00f3dulos anal\u00edticos; de \r\noadastro, de restri\u00e7\u00e4o e de comportamento, agregando tamb\u00e9m o M\u00f3dulo Score de \r\nCredito a partir de um conjunto de informa\u00e7\u00f6es pessoais passadas pelo Cliente no \r\nmomento do cadastro. \r\n\r\nA partir dos resultados obtidos dos M\u00f3dulos, o sistema disponibilizara informa\u00e7\u00f6es \r\n(positivas e negativas), possibilitando agilidade e seguran\u00e7a para decis\u00e4o autom\u00e1tica \r\nou manual. \r\n\r\nOs M\u00f3dulos s\u00e4o parametriz\u00e1veis a partir da Pol\u00edtica de Cr\u00e9dito do Cliente."},{"created_on":"2012/11/30 18:42:48 -0200","identifier":"dbbinder","updated_on":"2012/11/30 18:42:48 -0200","name":"dbbinder","id":13,"description":""},{"created_on":"2013/06/12 11:10:11 -0300","identifier":"iposms","updated_on":"2013/06/12 11:10:11 -0300","name":"IPoSMS","id":26,"description":"API that enables mobile device to communicate with internet hosts though SMS messages."},{"created_on":"2012/08/14 12:10:51 -0300","identifier":"iptv-orange","updated_on":"2012/08/14 14:36:02 -0300","name":"IPTV Orange","id":2,"description":""},{"created_on":"2012/08/15 10:28:26 -0300","identifier":"iptv-orange-pmb","updated_on":"2012/10/16 14:20:53 -0300","name":"OPM","parent":{"name":"IPTV Orange","id":2},"id":8,"description":"h2. Orange Package Manager\r\n\r\nBase para todos OPMs\r\nO OPMB atuar\u00e1 como o controlador do sistema de IPTV, sendo sua *responsabilidade* *controlar* que *informa\u00e7\u00e3o* ir\u00e1 para os stb's.\r\nSendo assim, fica a cargo do OPMB resolver qual lista de canais um dado stb deve receber, quais propagandas e qual SN o stb usar\u00e1 para receber conte\u00fado.\r\n\r\nO OPMG dever\u00e1 ter uma interface web para que o operador do sistema de IPTV seja capaz de configurar as regras do OPMB. Essas regras incluem, mas n\u00e3o se limitam a:\r\n - configurar pacote de canais\r\n - configurar pacote de canais para um dado cliente\r\n - configurar regi\u00f5es de audi\u00eancia\r\n"},{"created_on":"2012/10/01 14:07:12 -0300","identifier":"opmbweb","updated_on":"2012/10/16 14:21:14 -0300","name":"OPMG - Web","parent":{"name":"OPM","id":8},"id":10,"description":"Interface web para configura\u00e7\u00e3o do OPMB. \r\nEsse sistema ser\u00e1 utilizados pelo operadores da empresa de tv por assinatura e permitir\u00e1 que eles configurem:\r\n- pacotes de canais\r\n- qual pacote de canal um cliente possui\r\n- definir regi\u00f5es de audi\u00eancia\r\n- liberar conte\u00fados pay-per-view para clientes\r\n...\r\n"},{"created_on":"2012/08/14 21:18:34 -0300","identifier":"iptv-orange-stb","updated_on":"2013/05/07 11:00:40 -0300","name":"STB-C++","parent":{"name":"IPTV Orange","id":2},"id":7,"description":""},{"created_on":"2012/10/16 14:30:21 -0300","identifier":"stbg","updated_on":"2012/10/16 14:30:21 -0300","name":"STB-G - GUI do STB","parent":{"name":"STB-C++","id":7},"id":11,"description":"Interface gr\u00e1fica do STB em (principalmente) QML+JS que ser\u00e1 customizada pelos operadores de IPTV."},{"created_on":"2012/11/14 19:48:07 -0200","identifier":"stbhtml","updated_on":"2012/11/14 19:48:07 -0200","name":"STB-HTML","parent":{"name":"IPTV Orange","id":2},"id":12,"description":"Vers\u00e3o HTML do software que roda no STB"},{"created_on":"2013/08/21 10:44:35 -0300","identifier":"telemetria","updated_on":"2013/08/21 10:44:35 -0300","name":"Telemetria","id":27,"description":""}],"total_count":19,"limit":25,"offset":0}" 
            
            RMProject p;
        }
    }
}
